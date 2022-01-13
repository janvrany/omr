/*******************************************************************************
 * Copyright IBM Corp. and others 2023
 *
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License 2.0 which accompanies this
 * distribution and is available at https://www.eclipse.org/legal/epl-2.0/
 * or the Apache License, Version 2.0 which accompanies this distribution
 * and is available at https://www.apache.org/licenses/LICENSE-2.0.
 *
 * This Source Code may also be made available under the following Secondary
 * Licenses when the conditions for such availability set forth in the
 * Eclipse Public License, v. 2.0 are satisfied: GNU General Public License,
 * version 2 with the GNU Classpath Exception [1] and GNU General Public
 * License, version 2 with the OpenJDK Assembly Exception [2].
 *
 * [1] https://www.gnu.org/software/classpath/license.html
 * [2] https://openjdk.org/legal/assembly-exception.html
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0-only WITH Classpath-exception-2.0 OR GPL-2.0-only WITH OpenJDK-assembly-exception-1.0
 *******************************************************************************/

#ifndef RVINSTRUCTIONUTILS_INCL
#define RVINSTRUCTIONUTILS_INCL

#include <stddef.h>
#include <stdint.h>
#include <riscv.h>

#include "codegen/Register.hpp"
#include "codegen/RealRegister.hpp"
#include "codegen/InstOpCode.hpp"

#define RISCV_INSTRUCTION_LENGTH 4

/**
 * ==== R-type ====
 */

static inline uint32_t
TR_RISCV_RTYPE(uint32_t insn, uint32_t rd, uint32_t rs1, uint32_t rs2)
   {
   return ((insn) | ((rd) << OP_SH_RD) | ((rs1) << OP_SH_RS1) | ((rs2) << OP_SH_RS2));
   }

static inline uint32_t
TR_RISCV_RTYPE(TR::InstOpCode::Mnemonic insn, TR::RealRegister::RegNum rd, TR::RealRegister::RegNum rs1, TR::RealRegister::RegNum rs2)
   {
   return TR_RISCV_RTYPE(TR::InstOpCode::getOpCodeBinaryEncoding(insn), TR::RealRegister::binaryRegCode(rd), TR::RealRegister::binaryRegCode(rs1), TR::RealRegister::binaryRegCode(rs2));
   }

static inline uint32_t
TR_RISCV_RTYPE(TR::InstOpCode::Mnemonic insn, TR::Register *rd, TR::Register *rs1, TR::Register *rs2)
   {
   return TR_RISCV_RTYPE(insn, toRealRegister(rd)->getRegisterNumber(), toRealRegister(rs1)->getRegisterNumber(), toRealRegister(rs2)->getRegisterNumber());
   }

/**
 * ==== I-type ====
 */

static inline uint32_t
TR_RISCV_ITYPE(uint32_t insn, uint32_t rd, uint32_t rs1, uint32_t imm)
   {
   return ((insn) | ((rd) << OP_SH_RD) | ((rs1) << OP_SH_RS1) | ENCODE_ITYPE_IMM(imm));
   }

static inline uint32_t
TR_RISCV_ITYPE(TR::InstOpCode::Mnemonic insn, TR::RealRegister::RegNum rd, TR::RealRegister::RegNum rs1, uint32_t imm)
   {
   return TR_RISCV_ITYPE(TR::InstOpCode::getOpCodeBinaryEncoding(insn), TR::RealRegister::binaryRegCode(rd), TR::RealRegister::binaryRegCode(rs1), imm);
   }

static inline uint32_t
TR_RISCV_ITYPE(TR::InstOpCode::Mnemonic insn, TR::Register *rd, TR::Register *rs1, uint32_t imm)
   {
   return TR_RISCV_ITYPE(insn, toRealRegister(rd)->getRegisterNumber(), toRealRegister(rs1)->getRegisterNumber(), imm);
   }

/**
 * ==== S-type ====
 */

static inline uint32_t
TR_RISCV_STYPE(uint32_t insn, uint32_t rs1, uint32_t rs2, uint32_t imm)
   {
   return ((insn) | ((rs1) << OP_SH_RS1) | ((rs2) << OP_SH_RS2) | ENCODE_STYPE_IMM(imm));
   }

static inline uint32_t
TR_RISCV_STYPE(TR::InstOpCode::Mnemonic insn, TR::RealRegister::RegNum rs1, TR::RealRegister::RegNum rs2, uint32_t imm)
   {
   return TR_RISCV_STYPE(TR::InstOpCode::getOpCodeBinaryEncoding(insn), TR::RealRegister::binaryRegCode(rs1), TR::RealRegister::binaryRegCode(rs2), imm);
   }

static inline uint32_t
TR_RISCV_STYPE(TR::InstOpCode::Mnemonic insn, TR::Register *rs1, TR::Register *rs2, uint32_t imm)
   {
   return TR_RISCV_STYPE(insn, toRealRegister(rs1)->getRegisterNumber(), toRealRegister(rs2)->getRegisterNumber(), imm);
   }

/**
 * ==== B-type ====
 */

static inline uint32_t
TR_RISCV_SBTYPE(uint32_t insn, uint32_t rs1, uint32_t rs2, uint32_t imm)
   {
   return ((insn) | ((rs1) << OP_SH_RS1) | ((rs2) << OP_SH_RS2) | ENCODE_SBTYPE_IMM(imm));
   }

static inline uint32_t
TR_RISCV_SBTYPE(TR::InstOpCode::Mnemonic insn, TR::RealRegister::RegNum rs1, TR::RealRegister::RegNum rs2, uint32_t imm)
   {
   return TR_RISCV_SBTYPE(TR::InstOpCode::getOpCodeBinaryEncoding(insn), TR::RealRegister::binaryRegCode(rs1), TR::RealRegister::binaryRegCode(rs2), imm);
   }

static inline uint32_t
TR_RISCV_SBTYPE(TR::InstOpCode::Mnemonic insn, TR::Register *rs1, TR::Register *rs2, uint32_t imm)
   {
   return TR_RISCV_SBTYPE(insn, toRealRegister(rs1)->getRegisterNumber(), toRealRegister(rs2)->getRegisterNumber(), imm);
   }

/**
 * ==== U-type ====
 */

static inline uint32_t
TR_RISCV_UTYPE(uint32_t insn, uint32_t rd, uint32_t bigimm)
   {
   return ((insn) | ((rd) << OP_SH_RD) | ENCODE_UTYPE_IMM(bigimm));
   }

static inline uint32_t
TR_RISCV_UTYPE(TR::InstOpCode::Mnemonic insn, TR::RealRegister::RegNum rd, uint32_t bigimm)
   {
   return TR_RISCV_UTYPE(TR::InstOpCode::getOpCodeBinaryEncoding(insn), TR::RealRegister::binaryRegCode(rd), bigimm);
   }

static inline uint32_t
TR_RISCV_UTYPE(TR::InstOpCode::Mnemonic insn, TR::Register *rd, uint32_t bigimm)
   {
   return TR_RISCV_UTYPE(insn, toRealRegister(rd)->getRegisterNumber(), bigimm);
   }

/**
 * ==== J-type ====
 */

static inline uint32_t
TR_RISCV_UJTYPE(uint32_t insn, uint32_t rd, uint32_t target)
   {
   return ((insn) | ((rd) << OP_SH_RD) | ENCODE_UJTYPE_IMM(target));
   }

static inline uint32_t
TR_RISCV_UJTYPE(TR::InstOpCode::Mnemonic insn, TR::RealRegister::RegNum rd, uint32_t bigimm)
   {
   return TR_RISCV_UJTYPE(TR::InstOpCode::getOpCodeBinaryEncoding(insn), TR::RealRegister::binaryRegCode(rd), bigimm);
   }

static inline uint32_t
TR_RISCV_UJTYPE(TR::InstOpCode::Mnemonic insn, TR::Register *rd, uint32_t target)
   {
   return TR_RISCV_UJTYPE(insn, toRealRegister(rd)->getRegisterNumber(), target);
   }

static inline uint32_t
TR_RISCV_UJTYPE(TR::InstOpCode &insn, TR::Register *rd, uint32_t target)
   {
   return TR_RISCV_UJTYPE(insn.getMnemonic(), rd, target);
   }

/**
 * \brief Extracts (hiBit,loBit) from 64bit value, starting at bit 'hiBit'. Lowest bit is bit 0,
 * highest bit is bit 63.
 */
static inline uint64_t extractBits(uint64_t value, uint64_t hiBit, uint64_t loBit)
   {
   TR_ASSERT_FATAL(hiBit <  64,          "Value of 'hiBit' must be less than 64");
   TR_ASSERT_FATAL(loBit <= hiBit,       "Value of 'loBit' must be less or equal to hiBit");

   return (value >> loBit) & ~(~UINT64_C(0) << (hiBit - loBit + 1));
   }

/**
 * @brief Loads 32bits into @param trgReg. This method generate sequence of 
 * instructions:
 * 
 *     lui  trgReg, bits<31,12>(value)
 *     addi trgReg, trgReg, bits<11,0>(value)
 * 
 * This sequence is *always* generated, even if shorter sequence is possible.
 * In other words, this function *always* generates 8bytes worth of 
 * instructions.
 * 
 * @param buffer pointer to code buffer where the code is generated
 * @param trgReg register where to load 32bit constant
 * @param value constant value to load
 * @return pointer to code buffer pointing past the last instruction (addi).
 */
static inline uint8_t *loadConstant32(uint8_t *buffer, TR::RealRegister::RegNum trgReg, int32_t value)
   {
   uint32_t *cursor = reinterpret_cast<uint32_t*>(buffer);
   uint32_t lo = (uint32_t)value & ~(0xFFFFFFFF << RISCV_IMM_BITS);
   uint32_t hi = (uint32_t)value & (0xFFFFFFFF << RISCV_IMM_BITS);

   /*
   * Since addi is signed add and sign-extends its 12bit immediate operand to
   * XLEN bits, the value of %hi(value) has to be adjusted if sign-bit of
   * %lo(value) is 1 (to compensate for fact that addi adds negative value).
   */
   if (lo & (1 << (RISCV_IMM_BITS - 1)))
      {
      hi += 1 << RISCV_IMM_BITS;
      }
   
   *cursor++ = TR_RISCV_UTYPE(TR::InstOpCode::_lui, trgReg, hi);
   *cursor++ = TR_RISCV_ITYPE(TR::InstOpCode::_addiw, trgReg, trgReg, lo);
   
   TR_ASSERT_FATAL((reinterpret_cast<uint8_t*>(cursor) - buffer) == 8, "Less than 8 bytes generated");
   return reinterpret_cast<uint8_t*>(cursor);
   }

/**
 * @brief Loads 64bits into @param trgReg. This method generate following sequence
 * of instructions:
 * 
 *     lui  trgReg,         bits<63,44>(value)
 *     addi trgReg, trgReg, bits<43,32>
 *     slli trgReg, trgReg, 11
 *     addi trgReg, trgReg, bits<31,21>
 *     slli trgReg, trgReg, 11
 *     addi trgReg, trgReg, bits<20,10>
 *     slli trgReg, trgReg, 10
 *     addi trgReg, trgReg, bits<9,0> 
 * 
 * This sequence is *always* generated, even if shorter sequence is possible.
 * In other words, this function *always* generates 32bytes worth of 
 * instructions.
 * 
 * @param buffer pointer to code buffer where the code is generated
 * @param trgReg register where to load 32bit constant
 * @param value constant value to load
 * @return pointer to code buffer pointing past the last instruction (addi).
 */
static inline uint8_t *loadConstant64(uint8_t *buffer, TR::RealRegister::RegNum trgReg, int64_t value)
   {
   uint32_t *cursor;

   /*
    * Load high 32bits of value into low 32bits of trgReg
    */
   cursor = reinterpret_cast<uint32_t *>(loadConstant32(buffer, trgReg, extractBits(value, 63, 32)));

   /*
    * Now use sequence of slli + addi to shift-and-load low 32bits of value
    */
   *cursor++ = TR_RISCV_ITYPE(TR::InstOpCode::_slli, trgReg, trgReg, 11);
   *cursor++ = TR_RISCV_ITYPE(TR::InstOpCode::_addi, trgReg, trgReg, extractBits(value, 31, 21));

   *cursor++ = TR_RISCV_ITYPE(TR::InstOpCode::_slli, trgReg, trgReg, 11);
   *cursor++ = TR_RISCV_ITYPE(TR::InstOpCode::_addi, trgReg, trgReg, extractBits(value, 20, 10));

   *cursor++ = TR_RISCV_ITYPE(TR::InstOpCode::_slli, trgReg, trgReg, 10);
   *cursor++ = TR_RISCV_ITYPE(TR::InstOpCode::_addi, trgReg, trgReg, extractBits(value, 9, 0));

   TR_ASSERT_FATAL((reinterpret_cast<uint8_t*>(cursor) - buffer) == 32, "Less than 32 bytes generated");
   return reinterpret_cast<uint8_t*>(cursor);
   }


#endif // RVINSTRUCTIONUTILS_INCL
