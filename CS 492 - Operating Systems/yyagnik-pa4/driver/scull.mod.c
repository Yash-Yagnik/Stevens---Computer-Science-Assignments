#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif


static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x92997ed8, "_printk" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x4afe073f, "cdev_del" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x4dfa8d4b, "mutex_lock" },
	{ 0x37a0cba, "kfree" },
	{ 0x3213f038, "mutex_unlock" },
	{ 0x3fd78f3b, "register_chrdev_region" },
	{ 0xb41d8294, "cdev_init" },
	{ 0xe5bf1632, "cdev_add" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xd0da656b, "__stack_chk_fail" },
	{ 0x26601e5b, "current_task" },
	{ 0x4c12d3f3, "kmalloc_caches" },
	{ 0xdcf9792a, "kmalloc_trace" },
	{ 0x68f31cbd, "__list_add_valid" },
	{ 0x3a099605, "__get_user_nocheck_4" },
	{ 0x8d6aff89, "__put_user_nocheck_4" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0xb2dda52a, "param_ops_int" },
	{ 0x6093f1a5, "module_layout" },
};

MODULE_INFO(depends, "");

