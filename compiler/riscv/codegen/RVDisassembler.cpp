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

#include "codegen/RVDisassembler.hpp"
#include "env/OMRIO.hpp"

void
TR::RVDissasembler::fetch1(const uint8_t *buffer, Instruction *insn, size_t *insn_len)
   {
   inst_fetch(buffer, insn, insn_len);
   }

void
TR::RVDissasembler::disassemble1(TR::FILE *pOutFile, const uint8_t *buffer, const Instruction insn)
   {
   char assembly[80] = { 0 };
   disasm_inst(assembly, sizeof(assembly), rv64, static_cast<uint64_t>(reinterpret_cast<intptr_t>(buffer)), insn);
   trfprintf(pOutFile, "%s", assembly);
   }





