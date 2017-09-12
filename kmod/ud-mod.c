#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>

#include <linux/irq.h>
#include <linux/io.h>
#include <linux/irqdomain.h>
#include <linux/interrupt.h>
#include <linux/of.h>
#include <linux/of_address.h>

#define IRQ_N 6

irqreturn_t  ud_irq(int irq, void *dev_id)
//irqreturn_t  ud_irq(int irq, void *dev_id, struct pt_regs *regs)
{
	  printk("Got UD!\n");
}


static int __init onload(void) {
	printk(KERN_EMERG "UD mod loaded\n");
	int ret;

	ret = request_irq(IRQ_N, ud_irq,
			  IRQF_NO_SUSPEND,
                          "ud-mod", NULL);

	if (ret!=0) {
		printk("ERROR: Cannot request IRQ %d", IRQ_N);
		printk(" - code %d , EIO %d , EINVAL %d\n", ret, EIO, EINVAL);
	}
	  return 0;
}

static void __exit onunload(void) {
	  free_irq(IRQ_N, NULL);
	  printk(KERN_EMERG "UD mod removed\n");
}

module_init(onload);
module_exit(onunload);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vladimir Grachev");
MODULE_DESCRIPTION("I teach myself on handling #UD");

