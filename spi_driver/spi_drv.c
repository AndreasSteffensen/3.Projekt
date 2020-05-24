#include <linux/cdev.h> 
#include <linux/uaccess.h>  
#include <linux/module.h> 
#include <linux/spi/spi.h> 
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>

#define MAXLEN 32
#define MODULE_DEBUG 1   // Enable/Disable Debug messages

/* Char Driver Globals */
static struct spi_driver spi_drv_spi_driver;
struct file_operations spi_drv_fops;
static struct class *spi_drv_class;
static dev_t devno;
static struct cdev spi_drv_cdev;

/* Definition af SPI devices */
struct spi_devices {
  struct spi_device *spi;            
};
static struct spi_devices spi_devs[4]; 
static const int spi_devs_len = 4;  
static int spi_devs_cnt = 0;

/* Global variabler til interrupt GPIO */
unsigned int gpio_nr;
unsigned int gpio_dir;

/* Macro til håndtering af fejl */
#define ERRGOTO(label, ...)                     \
  {                                             \
    printk (__VA_ARGS__);                       \
    goto label;                                 \
  } while(0)

/*Global irq variables*/
static DECLARE_WAIT_QUEUE_HEAD(wq);
static int irq_line;
static int irq_flag = 0;

/*Interrupt handler*/
static irqreturn_t irq_handler(int irq, void *dev_id)
{
  irq_flag = 1;
  wake_up_interruptible(&wq);   // Herefter eksekveres spi_drv_read
  return IRQ_HANDLED;
}  

/*
 * Character Driver Module Init Method
 */
static int __init spi_drv_init(void)
{
  int err = 0;
  printk("spi_drv driver initializing\n");

  /* Alloker major numre og registrer fops*/
  err = alloc_chrdev_region(&devno, 0, 255, "spi_drv driver");
  if(MAJOR(devno) <= 0)
    ERRGOTO(err_no_cleanup, "Failed to register chardev\n");
    
  printk(KERN_ALERT "Assigned major no: %i\n", MAJOR(devno));
  cdev_init(&spi_drv_cdev, &spi_drv_fops);
  err = cdev_add(&spi_drv_cdev, devno, 255);
  if (err)
    ERRGOTO(err_cleanup_chrdev, "Failed to create class\n");

  /* Polulate sysfs entries */
  spi_drv_class = class_create(THIS_MODULE, "spi_drv_class");
  if (IS_ERR(spi_drv_class))
    ERRGOTO(err_cleanup_cdev, "Failed to create class\n");

  /* Registrer SPI Driver */
  /* Kalder probe, hvis device er tilstede */
  err = spi_register_driver(&spi_drv_spi_driver);
  if(err)
    ERRGOTO(err_cleanup_class, "Failed SPI Registration\n");

  return 0;

  /* Fejl ved initialisering af driveren */
 err_cleanup_class:
  class_destroy(spi_drv_class);
 err_cleanup_cdev:
  cdev_del(&spi_drv_cdev);
 err_cleanup_chrdev:
  unregister_chrdev_region(devno, 255);
 err_no_cleanup:
  return err;
}
/*
 * Character Driver Module Exit Method
 */
static void __exit spi_drv_exit(void)
{
  printk("spi_drv driver exit\n");
  spi_unregister_driver(&spi_drv_spi_driver);
  class_destroy(spi_drv_class);
  cdev_del(&spi_drv_cdev);
  unregister_chrdev_region(devno, 255);
}
/*
 * Character Driver Write File Operations Method
 */
ssize_t spi_drv_write(struct file *filep, const char __user *ubuf,
                      size_t count, loff_t *f_pos)
{
  /* Lokale variabler */
  int minor, len, err;
  char kbuf[MAXLEN];
  int value;

  /* Aflæs device minor nr. */
  minor = iminor(filep->f_inode);
  len = count < MAXLEN ? count : MAXLEN-1;

  /* Kopier data fra userspace til kernelspace */
  if(copy_from_user(kbuf, ubuf, len))
    return -EFAULT;

  kbuf[len] = '\0';
  sscanf(kbuf,"%i\n",&value);

  /* Initialisering af besked i overenstemmelse med Dr. pill protokol */
  u8 values[len];
  values[0] = 0xAA + minor;
  unsigned int divider = 1;
  
  if(minor !=1 )
  {
  for(unsigned int i = len; i > 0; i--)
  {
    values[i] = (value/divider)%10;
    divider *= 10;
  }
  }
  else
  {
    for(unsigned int i = len; i > 0; i--)
    {
      values[i]=value;
    }
  }

  /* Initialisering af spi besked */
  struct spi_transfer t[len+1];
  struct spi_message m;
  memset(t,0,sizeof(t));
  spi_message_init(&m);
  m.spi=spi_devs[minor].spi;

  for(unsigned int i = 0; i < len+1; i++)
  {
    t[i].tx_buf = &values[i];
    t[i].rx_buf = NULL;
    t[i].len = 1;
    spi_message_add_tail(&t[i],&m);
  }
    
  /* Afsend spi besked over spi bus */
  err = spi_sync(m.spi,&m);
  if( err < 0 )
  {
    printk(KERN_ALERT "Failed to read message from device spi@0 [minor] %i",minor);
  }

  *f_pos += len;
  return len;
}

/*
 * Character Driver Read File Operations Method
 */
ssize_t spi_drv_read(struct file *filep, char __user *ubuf,
                     size_t count, loff_t *f_pos)
{
  /* spi_drv_read er blokerende */
  wait_event_interruptible(wq, irq_flag!=0);
  irq_flag = 0;

  /* Lokale variabler */
  int minor, len;
  unsigned char result = 1;
  char resultBuf[MAXLEN];
  
  /* Aflæs device minor nr. */
  minor = iminor(filep->f_inode);

  /* Initialisering af besked i overenstemmelse med Dr. pill protokol */
  u8 cmd = 0xA0 + minor;

  /* Initialisering af spi besked */
  struct spi_transfer t[2];
  struct spi_message m;
  memset(t,0,sizeof(t));
  spi_message_init(&m);
  m.spi=spi_devs[minor].spi;

  /* Spørg efter PSoC status */
  t[0].tx_buf = &cmd;
  t[0].rx_buf = NULL;
  t[0].len = 1;
  t[0].delay_usecs = 20;
  spi_message_add_tail(&t[0],&m);

  /* Modtag PSoC status */
  t[1].tx_buf = NULL;
  t[1].rx_buf = &result;
  t[1].len = 1;
  spi_message_add_tail(&t[1],&m);
  
  /* Afsend spi besked over spi bus */
  int err = spi_sync(m.spi,&m);
  if( err < 0 )
  {
    printk(KERN_ALERT "Failed to read message from device spi@0 [minor] %i",minor);
  }
  
  len = snprintf(resultBuf, count, "%u\n", result);
  resultBuf[len] = '\0';
  
  /* Kopier PSoC status til userspace */
  if(copy_to_user(ubuf, resultBuf, len))
    return -EFAULT;
  
  *f_pos += len;
  return len;
}

struct file_operations spi_drv_fops =
  {
    .owner   = THIS_MODULE,
    .write   = spi_drv_write,
    .read    = spi_drv_read,
  };
/**********************************************************
 * LINUX DEVICE MODEL METHODS (spi)
 **********************************************************/
/*
 * spi_drv Probe
 * Called when a device with the name "spi_drv" is
 * registered.
 */
static int spi_drv_probe(struct spi_device *sdev)
{
  int err = 0;
  struct device *dev = &sdev->dev;
  struct device_node *np = dev->of_node;

  /*GPIO nr. from devicetree*/
  gpio_nr = of_get_gpio(np, 0);
  if(gpio_nr < 0)
  {
    if(gpio_nr != -EPROBE_DEFER)
      dev_err(dev,"Failed to parse io %d\n", gpio_nr);
  }

  /*Request GPIO resources*/
  err = gpio_request(gpio_nr, "spi_drv_gpio");
  if(err < 0)
  {
    printk(KERN_ALERT"ERROR: %d\n", err);
    goto err_exit;
  }

  gpio_direction_input(gpio_nr);  

  /*Request irq line*/
  irq_line = gpio_to_irq(gpio_nr);
  err = request_irq(irq_line, irq_handler, IRQF_TRIGGER_FALLING, "GPIO_interrupt", NULL);
  if(err < 0)
  {
    printk("Failed aquire irq\n");
    goto err_irq_unregister;
  }
  printk("GPIO %d got irq-line: %d\n", gpio_nr, irq_line);

  struct device *spi_drv_device;
  printk(KERN_DEBUG "New SPI device: %s using chip select: %i\n",
         sdev->modalias, sdev->chip_select);
  /* Check we are not creating more
     devices than we have space for */
  if (spi_devs_cnt > spi_devs_len) {
    printk(KERN_ERR "Too many SPI devices for driver\n");
    return -ENODEV;
  }
  /* Configure bits_per_word, always 8-bit for RPI!!! */
  sdev->bits_per_word = 8;
  spi_setup(sdev);
  /* Create devices, populate sysfs and
     active udev to create devices in /dev */
  for(;spi_devs_cnt < 4; spi_devs_cnt++)
  {
    /* We map spi_devs index to minor number here */
    spi_drv_device = device_create(spi_drv_class, NULL,
                                  MKDEV(MAJOR(devno), spi_devs_cnt),
                                  NULL, "spi_drv%d", spi_devs_cnt);
    if (IS_ERR(spi_drv_device))
    {
      printk(KERN_ALERT "FAILED TO CREATE DEVICE\n");
      goto err_free_buf;
    }
    else
      printk(KERN_ALERT "Using spi_devs%i on major:%i, minor:%i\n",
            spi_devs_cnt, MAJOR(devno), spi_devs_cnt);
    /* Update local array of SPI devices */
    spi_devs[spi_devs_cnt].spi = sdev;
  }
  return err;

  /*ERROR HANDLING*/
  err_irq_unregister:
    free_irq(irq_line, NULL);
  err_free_buf:
    gpio_free(gpio_nr);
  err_exit:
    return err;
}
/*
 * spi_drv Remove
 * Called when the device is removed
 * Can deallocate data if needed
 */
static int spi_drv_remove(struct spi_device *sdev)
{
  free_irq(irq_line, NULL);
  gpio_free(gpio_nr);

  for(;spi_devs_cnt > 0; spi_devs_cnt--)
  {
    printk (KERN_ALERT "Removing spi device\n");
    device_destroy(spi_drv_class, MKDEV(MAJOR(devno), spi_devs_cnt-1));
  }

  return 0;
}
/*
 * spi Driver Struct
 * Holds function pointers to probe/release
 * methods and the name under which it is registered
 */
static const struct of_device_id of_spi_drv_spi_device_match[] = {
  { .compatible = "ase, spi_drv", }, {},
};
static struct spi_driver spi_drv_spi_driver = {
  .probe      = spi_drv_probe,
  .remove     = spi_drv_remove,
  .driver     = {
    .name   = "spi_drv",
    .bus    = &spi_bus_type,
    .of_match_table = of_spi_drv_spi_device_match,
    .owner  = THIS_MODULE,
  },
};

module_init(spi_drv_init);
module_exit(spi_drv_exit);

MODULE_AUTHOR("Jens Nørby Kristensen & Lasse Andresen");
MODULE_LICENSE("GPL");