#pragma once
#include <stdint.h>
#include <vector>

namespace pdp11
{
     // after decoding the various different opcode types, the machine instruction
    // will be converted to one of these types
    enum class operation
    {
        // double operand
        move_word,
        move_byte,
        compare_word,
        compare_byte,
        bit_test_word,
        bit_test_byte,
        bit_clear_word,
        bit_clear_byte,
        bit_set_word,
        bit_set_byte,
        add_word,
        sub_word,

        // single operand
        swap_bytes,
        clear_word,
        clear_byte,
        complement_word,
        complement_byte,
        increment_word,
        increment_byte,
        decrement_word,
        decrement_byte,
        negate_word,
        negate_byte,
        add_carry_word,
        add_carry_byte,
        subtract_carry_word,
        subtract_carry_byte,
        test_word,
        test_byte,
        rotate_right_word,
        rotate_right_byte,
        rotate_left_word,
        rotate_left_byte,
        arithmetic_shift_right_word,
        arithmetic_shift_right_byte,
        arithmetic_shift_left_word,
        arithmetic_shift_left_byte,
        mark_processor_status,
        move_to_processor_status,
        move_from_prev_instruction,
        move_from_prev_data,
        move_to_prev_instruction,
        move_to_prev_data,
        sign_extend,
        move_from_processor_status,

        // branch
        branch_always,
        branch_not_equal,
        branch_equal,
        branch_greater_equal,
        branch_less,
        branch_greater,
        branch_less_equal,
        branch_plus,
        branch_minus,
        branch_higher,
        branch_lower_same,
        branch_overflow_clear,
        branch_overflow_set,
        branch_carry_clear,
        branch_carry_set,

        // condition code
        nop,
        set_carry,
        clear_carry,
        set_overflow,
        clear_overflow,
        set_zero,
        clear_zero,
        set_negative,
        clear_negative,
        set_all_cond,
        clear_all_cond,

        // misc
        jump_to_subroutine,
        return_from_subroutine,
        jump,
        halt,
        wait,
        return_from_interrupt,
        breakpoint_trap,
        reset,

        unused
    };

    struct decoded_instruction
    {
        operation op = operation::unused;
    };

    struct opcode_mask_instruction
    {
        uint16_t mask;
        uint16_t opcode;
        operation op;
    };

    class lsi11
    {
        public:
            static decoded_instruction decode(uint16_t instruction);

        private:
            static std::vector<opcode_mask_instruction> s_opcode_to_instruction_map;
    };
}