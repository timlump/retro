#include "lsi11.h"
#include <iostream>

namespace pdp11
{
    std::vector<lsi11::opcode_mask_instruction> lsi11::s_opcode_to_instruction_map = {
        // mask, instruction, operation
        // misc instruction with non standard formats
        {0xffff, 0b000, operation::halt},
        {0xffff, 0b001, operation::wait},
        {0xffff, 0b010, operation::return_from_interrupt},
        {0xffff, 0b100, operation::breakpoint_trap},
        {0xffff, 0b101, operation::reset},
        {0xff40, 0x0040, operation::jump},
        {0xff80, 0x0080, operation::return_from_subroutine},
        {0xf800, 0x0800, operation::jump_to_subroutine},
        {0xffc0, 0x00c0, operation::swap_bytes},

        // condition code operations - 0x00A means clear, 0x00B mmeans set
        {0xffff, 0x00a0, operation::nop},
        {0xffff, 0x00b0, operation::nop},
        {0xffff, 0x00a1, operation::clear_carry},
        {0xffff, 0x00b1, operation::set_carry},
        {0xffff, 0x00a2, operation::clear_overflow},
        {0xffff, 0x00b2, operation::set_overflow},
        {0xffff, 0x00a4, operation::clear_zero},
        {0xffff, 0x00b4, operation::set_zero},
        {0xffff, 0x00a8, operation::clear_negative},
        {0xffff, 0x00b8, operation::set_negative},
        {0xffff, 0x00af, operation::clear_all_cond},
        {0xffff, 0x00bf, operation::set_all_cond},

        // branches
        {0xff00, 0x0100, operation::branch_always},
        {0xff00, 0x0200, operation::branch_not_equal},
        {0xff00, 0x0300, operation::branch_equal},
        {0xff00, 0x0400, operation::branch_greater_equal},
        {0xff00, 0x0500, operation::branch_less},
        {0xff00, 0x0600, operation::branch_greater},
        {0xff00, 0x0700, operation::branch_less_equal},
        {0xff00, 0x8000, operation::branch_plus},
        {0xff00, 0x8100, operation::branch_minus},
        {0xff00, 0x8200, operation::branch_higher},
        {0xff00, 0x8300, operation::branch_lower_same},
        {0xff00, 0x8400, operation::branch_overflow_clear},
        {0xff00, 0x8500, operation::branch_overflow_set},
        {0xff00, 0x8600, operation::branch_carry_clear},
        {0xff00, 0x8700, operation::branch_carry_set},

        // double operand
        {0xf000, 0x1000, operation::move_word},
        {0xf000, 0x9000, operation::move_byte},

        {0xf000, 0x2000, operation::compare_word},
        {0xf000, 0xa000, operation::compare_byte},

        {0xf000, 0x3000, operation::bit_test_word},
        {0xf000, 0xb000, operation::bit_test_byte},
        
        {0xf000, 0x4000, operation::bit_clear_word},
        {0xf000, 0xc000, operation::bit_clear_byte},

        {0xf000, 0x5000, operation::bit_set_word},
        {0xf000, 0xd000, operation::bit_set_byte},

        {0xf000, 0x6000, operation::sub_word},
        {0xf000, 0xe000, operation::add_word},

        // single operand (0x0 means word, 0x8 means byte)
        {0xffc0, 0x0a00, operation::clear_word},
        {0xffc0, 0x8a00, operation::clear_byte},

        {0xffc0, 0x0a40, operation::complement_word},
        {0xffc0, 0x8a40, operation::complement_byte},
        
        {0xffc0, 0x0a80, operation::increment_word},
        {0xffc0, 0x8a80, operation::increment_byte},
        
        {0xffc0, 0x0ac0, operation::decrement_word},
        {0xffc0, 0x8ac0, operation::decrement_byte},

        {0xffc0, 0x0b00, operation::negate_word},
        {0xffc0, 0x8b00, operation::negate_byte},

        {0xffc0, 0x0b40, operation::add_carry_word},
        {0xffc0, 0x8b40, operation::add_carry_byte},

        {0xffc0, 0x0b80, operation::subtract_carry_word},
        {0xffc0, 0x8b80, operation::subtract_carry_byte},

        {0xffc0, 0x0bc0, operation::test_word},
        {0xffc0, 0x8bc0, operation::test_byte},

        {0xffc0, 0x0c00, operation::rotate_right_word},
        {0xffc0, 0x8c00, operation::rotate_right_byte},

        {0xffc0, 0x0c40, operation::rotate_left_word},
        {0xffc0, 0x8c40, operation::rotate_left_byte},

        {0xffc0, 0x0c80, operation::arithmetic_shift_right_word},
        {0xffc0, 0x8c80, operation::arithmetic_shift_right_byte},

        {0xffc0, 0x0cc0, operation::arithmetic_shift_left_word},
        {0xffc0, 0x8cc0, operation::arithmetic_shift_left_byte},

        {0xffc0, 0x0d00, operation::mark_processor_status},
        {0xffc0, 0x8d00, operation::move_to_processor_status},

        {0xffc0, 0x0d40, operation::move_from_prev_instruction},
        {0xffc0, 0x8d40, operation::move_from_prev_data},

        {0xffc0, 0x0d80, operation::move_to_prev_instruction},
        {0xffc0, 0x8d80, operation::move_to_prev_data},

        {0xffc0, 0x0dc0, operation::sign_extend},
        {0xffc0, 0x8dc0, operation::move_from_processor_status}
    };

    void lsi11::execute(const decoded_instruction& instruction)
    {
        switch(instruction.op)
        {
            // todo
            
            default:
                std::cerr << "Unrecognised instruction" << std::endl;
        }
    }

    decoded_instruction lsi11::decode(uint16_t instruction)
    {
        decoded_instruction result;

        for (auto iter : s_opcode_to_instruction_map) {
            if (instruction & iter.mask == iter.opcode) {
                result.op = iter.op;
                break;
            }
        }

        result.branch_dest = 0x00ff & instruction;
        result.destination = address(0x007f & instruction);
        result.source = address((instruction >> 7) & 0x7f);
        result.stack = (instruction >> 6) & 0x7;

        return result;
    }
}