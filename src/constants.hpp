/*
    tkr
    Calculation of turbocharger parameters.

    File: constants.hpp

    Copyright (C) 2014 Artem Petrov <pa2311@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include <vector>

#define CONFIGFILE     "tkr.conf"
#define SRCDATAFILE    "src.csv"
#define REPORTNAME     "TKR_calc_report"
#define PARAMDELIMITER "="
#define CSVDELIMETER   ";"
#define TABLECAPSTRNUM 1
#define ERRORMSGBLANK  "tkr ERROR =>\t"
#define WARNMSGBLANK   "tkr WARNING =>\t"
#define MSGBLANK       "tkr ->\t"

enum {
    ACTYPE_AIRAIR,
    ACTYPE_COOLANTAIR
};

const std::vector<std::string> colCaptions = {
    "n[min-1]",
    "Me[Nm]",
    "Ne[kW]",
    "Gfuel[kg/h]",
    "Gair[kg/h]",
    "B0[bar]",
    "S[kPa]",
    "Pk_lp[bar]",
    "Pks_lp[bar]",
    "Pk_hp[bar]",
    "Pks_hp[bar]",
    "Pt_hp[bar]",
    "Pt_lp[bar]",
    "Pr[kPa]",
    "T0[degC]",
    "Tk_lp[degC]",
    "Tks_lp[degC]",
    "Tk_hp[degC]",
    "Tks_hp[degC]",
    "Tt_hp[degC]",
    "Tt_lp[degC]",
    "Tr[degC]",
    "Tcool[degC]"
};

#define FTDEFACCUR 0.001
#define MAXITER 100.0

#endif // CONSTANTS_HPP
