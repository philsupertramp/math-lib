/**
 * File              : styling.h
 * Author            : Philipp Zettl <philipp.zettl@godesteem.de>
 * Date              : 28.09.2019
 * Last Modified Date: 28.09.2019
 * Last Modified By  : Philipp Zettl <philipp.zettl@godesteem.de>
 */
/**
 * lib/styling.h
 * Copyright (c) 2019 Philipp Zettl <philipp.zettl@godesteem.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef STYLING_H
#define STYLING_H
/*
 * Text based formatting
 */
#include <stdbool.h>
#include <stdio.h>

// font style
const char *NORMAL;
const char *BOLD;
// colors
const char *RED;
const char *GREEN;
const char *YELLOW;
const char *BLUE;
const char *MAGENTA;
const char *CYAN;
// reset
const char *RESET;


void cprint(const char *, bool, FILE*);

#endif
