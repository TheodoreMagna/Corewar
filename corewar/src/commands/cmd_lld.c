/*
** EPITECH PROJECT, 2023
** Corewar
** File description:
** instruction live for the VM
*/

#include "vm.h"
#include "instructions.h"

/*
Similar to ld without the % IDX_MOD. This operation modifies the carry
*/
int lld_to_reg(vm_t *vm, process_t *process, char *type, int *size)
{
    int value = 0;
    int tot = 0;
    int pos = 0;

    pos = process->index;
    process->index += 2;
    value = param_getter(process, vm, type[0], size[0]);
    if (type[0] == IND_CODE) {
        tot = pos + value;
        value = cbuffer_geti(vm->arena, tot);
    }
    if (value != 0) {
        process->carry = 1;
    }
    set_reg(process, vm, value);
    return value;
}

void cmd_lld(vm_t *vm, process_t *process)
{
    char coding_byte = '\0';
    char command = '\0';
    char *type = NULL;
    int *size = NULL;

    command = cbuffer_getb(vm->arena, process->index);
    coding_byte = cbuffer_getb(vm->arena, process->index + 1);
    type = get_coding_byte(coding_byte);
    size = get_size(type, command - 1);
    if (command != 13 || !param_checker(type, command - 1)) {
        kill_process(process, vm);
    } else {
        ld_to_reg(vm, process, type, size);
    }
    free(type);
    free(size);
}

