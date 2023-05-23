/*
** EPITECH PROJECT, 2023
** corewar [WSL: fedora]
** File description:
** instruction_getter
*/

#include "vm.h"
#include "cbuffer.h"
#include "serrorh.h"
#include "instructions.h"

static const instruction_t instructions[] = {
    {&cmd_live, 10},
    {&cmd_ld, 5},
    {&cmd_st, 5},
    {&cmd_add, 10},
    {&cmd_sub, 10},
    {&cmd_and, 6},
    {&cmd_or, 6},
    {&cmd_xor, 6},
    {&cmd_zjmp, 20},
    {&cmd_ldi, 25},
    {&cmd_sti, 25},
    {&cmd_fork, 800},
    {&cmd_lld, 10},
    {&cmd_lldi, 50},
    {&cmd_lfork, 1000},
    {&cmd_aff, 2},
};

/**
 * @brief if instruction byte is not valid, set cmd to NULL WILL BE VERIFIED
 * set countdown to the corresponding intruction
 *
 * @param data process to handle (get instruction)
 * @param vm_ptr a pointer to the vm
 * @param none unused
 */
static void instruction_get_process(any_t data, void *vm_ptr, UNUSED void *none)
{
    vm_t *vm = vm_ptr;
    process_t *process = data;
    char instruction_byte = 0;

    instruction_byte = cbuffer_getb(vm->arena, process->index);
    if (instruction_byte < 1 || instruction_byte > 16) {
        process->instruction = NULL;
        process->cycle_to_wait = 0;
        return;
    }
    process->instruction = instructions[instruction_byte - 1].command;
    process->cycle_to_wait = instructions[instruction_byte - 1].cycles;
}

void instruction_get(vm_t *vm)
{
    list_foreach_wargs(vm->process, &instruction_get_process, vm, NULL);
}

/**
 * @brief return false if the reg is not valid
 * 
 * @param process 
 * @param vm 
 * @param type 
 * @param size 
 * @return int 
 */
bool get_param_value(process_t *process, char type, int *param)
{
    if (type == REG_CODE && *param == -1) {
        return false;
    }
    if (type == REG_CODE) {
        *param = process->registr[*param - 1];
    }
    return true;
}