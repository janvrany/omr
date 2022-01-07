/*******************************************************************************
 * Copyright (c) 2021, 2023 IBM Corp. and others
 *
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License 2.0 which accompanies this
 * distribution and is available at http://eclipse.org/legal/epl-2.0
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
 * [2] http://openjdk.java.net/legal/assembly-exception.html
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0 WITH Classpath-exception-2.0 OR LicenseRef-GPL-2.0 WITH Assembly-exception
 *******************************************************************************/

#ifndef RVDISASSEMBLER_INCL
#define RVDISASSEMBLER_INCL

#include <cstddef>
#include <cstdint>

extern "C" {
#include "third_party/riscv-disassembler/src/riscv-disas.h"
}

#include "env/FilePointer.hpp"

namespace TR
{

class RVDissasembler {
public:
    typedef rv_inst Instruction;

    /**
     * @brief Fetch one instruction from @param buffer and write it to
     * output parameter @param insn. Fetched instruction length in bytes
     * is written to output parameter @param insn_len. 
     * 
     * Note that in general, RISC-V supports compressed 16bit instructions 
     * (though not yet used in OMR.)
     * 
     * @param buffer pointer to code buffer with the instruction to disasemble.
     * @param insn pointer where to write fetched instruction.
     * @param insn_len pointer where to write fetched instruction length.
     */
    static void fetch1(const uint8_t *buffer, Instruction *insn, size_t *insn_len);

    /**
     * @brief Disassemble a single instruction and print it to the output. Instruction address
     * nor bytes are printed. 
     * 
     * @param pOutFile output disassembly is written.
     * @param buffer pointer to instruction to dissasemble.
     * @param insn instruction to disassemble, obtained by fetch1()
     */
    static void disassemble1(TR::FILE *pOutFile, const uint8_t *buffer, const Instruction insn);
};

} // namespace TR

#endif // RVDISASSEMBLER_INCL
