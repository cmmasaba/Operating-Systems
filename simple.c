#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

/**
 * struct birthday - a linked list containing details about birthdays
 * @name: the name of the person
 * @day: the day of birth
 * @month: the month of birth
 * @year: the year of birth
 * @list_head list: this structure is defined in the <linux/types.h>, it is
 * supposed to embed the linked list among the nodes that comprise the list
 *
 * Description:
 * this is a circular, doubly linked list.
 * It is designed to modify the kernel modules below so that they use the 
 * linked list structure. 
 */
typedef struct
{
	char *name;
	int day;
	int month;
	int year;
	struct list_head list;
} birthday;

/**
 * declare the list_head object that will be used as a reference
 * to the head of the linked list
 */
static LIST_HEAD(birthday_list);

/**
 * simple_init - function invoked when a module is loaded into the kernel
 *
 * Return: 0 always success
 */
int simple_init (void)
{
	birthday *Dan, *Mary, *Collins, *Felix, *Fely, *ptr;

	/* create 5 objects and initialize them */
	Dan = kmalloc(sizeof(*Dan), GFP_KERNEL);
	Dan->name = "Dan";
	Dan->day = 11;
	Dan->month = 2;
	Dan->year = 1990;
	INIT_LIST_HEAD(&Dan->list);/* initialize the list member in the struct birthday */
	list_add_tail(&Dan->list, &birthday_list);/* add the instance to the end of the linked list */

	Mary = kmalloc(sizeof(*Mary), GFP_KERNEL);
	Mary->name = "Mary";
	Mary->day = 21;
	Mary->month = 3;
	Mary->year = 2005;
	INIT_LIST_HEAD(&Mary->list);
	list_add_tail(&Mary->list, &birthday_list);

	Collins = kmalloc(sizeof(*Collins), GFP_KERNEL);
	Collins->name = "Collins";
	Collins->day = 16;
	Collins->month = 4;
	Collins->year = 1981;
	INIT_LIST_HEAD(&Collins->list);
	list_add_tail(&Collins->list, &birthday_list);

	Felix = kmalloc(sizeof(*Felix), GFP_KERNEL);
	Felix->name = "Felix";
	Felix->day = 13;
	Felix->month = 5;
	Felix->year = 2000;
	INIT_LIST_HEAD(&Felix->list);
	list_add_tail(&Felix->list, &birthday_list);

	Fely = kmalloc(sizeof(*Fely), GFP_KERNEL);
	Fely->name = "Fely";
	Fely->day = 4;
	Fely->month = 8;
	Fely->year = 1998;
	INIT_LIST_HEAD(&Fely->list);
	list_add_tail(&Fely->list, &birthday_list);

	printk(KERN_INFO "Loading module into the kernel.\n");
	
	/* traversing the linked list and printing info about the objects */
	/* list_for_each_entry() macro accepts three arguments respectively */
	/* a pointer to the struct being iterated over */
	/* a pointer to the head of the list being iterated over */
	/* the name of the variable containing the list_head structure */
	list_for_each_entry(ptr, &birthday_list, list)
	{
		printk(KERN_INFO "%s's birthday is, %i/%i/%.2i", ptr->name,
				ptr->day, ptr->month, ptr->year % 100);
	}

	return (0);
}

/**
 * simple_exit - function invoked when a module is removed from the kernel
 *
 * Return: no return value
 */
void simple_exit (void)
{
	birthday *ptr, *next;
	
	printk(KERN_INFO "Removing module from the kernel.\n");

	/* Removing elements from the linked list */
	/* use list_for_each_entry_safe () macro to traverse the list */
	/* then use the list_del() macro to delete each element */
	list_for_each_entry_safe(ptr, next, &birthday_list, list)
	{
		list_del(&ptr->list);
		kfree(ptr);
	}
}

/* macros for registering the module and exit points */
module_init(simple_init);
module_exit(simple_exit);

/* details about the software license, description and authour */
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
