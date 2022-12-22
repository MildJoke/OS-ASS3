#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/unistd.h>
#include <linux/syscalls.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");
MODULE_VERSION("0.01");

int pid = 0;
module_param(pid, int, 0);

static int __init q3_init(void)
{
    struct task_struct *t1;
    t1 = pid_task(find_vpid(pid), PIDTYPE_PID);
   
    printk(KERN_INFO "The pid is: %d\n", t1->pid);
    printk(KERN_INFO "The uid is: %d\n", t1->cred->uid.val);
    printk(KERN_INFO "The pgid is: %d\n", t1->group_leader->pid);
    printk(KERN_INFO "The comm is: %s\n", t1->comm);
    return 0;
}
static void __exit q3_exit(void)
{
    printk(KERN_INFO "Bye\n");
}
module_init(q3_init);
module_exit(q3_exit);