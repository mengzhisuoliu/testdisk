/*

    File: file_wallet.c

    Copyright (C) 2013 Christophe GRENIER <grenier@cgsecurity.org>
  
    This software is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
  
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
  
    You should have received a copy of the GNU General Public License along
    with this program; if not, write the Free Software Foundation, Inc., 51
    Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

 */

#if !defined(SINGLE_FORMAT) || defined(SINGLE_FORMAT_wallet)
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif
#include <stdio.h>
#include "types.h"
#include "filegen.h"

/*@ requires valid_register_header_check(file_stat); */
static void register_header_check_wallet(file_stat_t *file_stat);

const file_hint_t file_hint_wallet = {
  .extension = "wallet",
  .description = "Armory and multibit wallets",
  .max_filesize = 10 * 1024 * 1024,
  .recover = 1,
  .enable_by_default = 1,
  .register_header_check = &register_header_check_wallet
};

/*@
  @ requires separation: \separated(&file_hint_wallet, buffer+(..), file_recovery, file_recovery_new);
  @ requires valid_header_check_param(buffer, buffer_size, safe_header_only, file_recovery, file_recovery_new);
  @ ensures  valid_header_check_result(\result, file_recovery_new);
  @ assigns  *file_recovery_new;
  @*/
static int header_check_wallet(const unsigned char *buffer, const unsigned int buffer_size, const unsigned int safe_header_only, const file_recovery_t *file_recovery, file_recovery_t *file_recovery_new)
{
  reset_file_recovery(file_recovery_new);
  file_recovery_new->extension = file_hint_wallet.extension;
  return 1;
}

static void register_header_check_wallet(file_stat_t *file_stat)
{
  static const unsigned char armory_wallet[8] = {
    0xba, 'W', 'A', 'L', 'L', 'E', 'T', 0x00
  };
  static const unsigned char multibit_bitcoin[2+0x16]  = { 0x0a, 0x16, 'o', 'r', 'g', '.', 'b', 'i', 't', 'c', 'o', 'i', 'n', '.', 'p', 'r', 'o', 'd', 'u', 'c', 't', 'i', 'o', 'n' };
  static const unsigned char multibit_dogecoin[2+0x17] = { 0x0a, 0x17, 'o', 'r', 'g', '.', 'd', 'o', 'g', 'e', 'c', 'o', 'i', 'n', '.', 'p', 'r', 'o', 'd', 'u', 'c', 't', 'i', 'o', 'n' };
  register_header_check(0, armory_wallet, sizeof(armory_wallet), &header_check_wallet, file_stat);
  register_header_check(0, multibit_bitcoin, sizeof(multibit_bitcoin), &header_check_wallet, file_stat);
  register_header_check(0, multibit_dogecoin, sizeof(multibit_dogecoin), &header_check_wallet, file_stat);
}
#endif
