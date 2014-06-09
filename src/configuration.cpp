/*
    tkr
    Calculation of turbocharger parameters.

    File: configuration.cpp

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

#include "configuration.hpp"
#include "constants.hpp"
#include "identification.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define BOOST_NO_CXX11_SCOPED_ENUMS

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

using std::cout;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;

Configuration::Configuration() {
}

void Configuration::readConfigFile() {

    const boost::filesystem::path cfgfile(CONFIGFILE);

    if ( !boost::filesystem::exists(cfgfile) ) {

        cout << ERRORMSGBLANK << "Cofiguration file \"" << CONFIGFILE << "\" not found!\n"
             << MSGBLANK << Identification{}.name() << " will create blank of configuration.\n"
             << MSGBLANK << "Please edit file \"" << CONFIGFILE << "\".\n";

        if ( !createBlank() ) {
            cout << ERRORMSGBLANK << "Can not create file \"" << CONFIGFILE << "\"!\n"
                 << WARNMSGBLANK << "Default values will be used.\n";
        }

        return;
    }

    ifstream fin(CONFIGFILE);

    if ( !fin ) {
        cout << ERRORMSGBLANK << "Can not open file \"" << CONFIGFILE << "\" to read!\n";
        return;
    }

    string s;
    vector<string> elem;

    while ( !fin.eof() ) {

        getline(fin, s);

        if ( !s.empty() ) {

            boost::split(elem, s, boost::is_any_of(PARAMDELIMITER));

            if ( elem.size() != 2 ) {

                s.clear();
                elem.clear();

                continue;
            }

            if ( elem[0] == "testObjDescr" ) {
                m_testObjDescr = elem[1];
            }
            else if ( elem[0] == "acTypelp" ) {
                m_acType_lp = boost::lexical_cast<size_t>(elem[1]);
            }
            else if ( elem[0] == "acTypehp" ) {
                m_acType_hp = boost::lexical_cast<size_t>(elem[1]);
            }
            else if ( elem[0] == "B0_std" ) {
                m_B0_std = boost::lexical_cast<double>(elem[1]);
            }
            else if ( elem[0] == "T0_std" ) {
                m_T0_std = boost::lexical_cast<double>(elem[1]);
            }
            else if ( elem[0] == "Vh" ) {
                m_Vh = boost::lexical_cast<double>(elem[1]);
            }
            else if ( elem[0] == "F1_S" ) {
                m_F1_S = boost::lexical_cast<double>(elem[1]);
            }
            else if ( elem[0] == "F2_Pklp" ) {
                m_F2_Pklp = boost::lexical_cast<double>(elem[1]);
            }
            else if ( elem[0] == "F3_Pkslp" ) {
                m_F3_Pkslp = boost::lexical_cast<double>(elem[1]);
            }
            else if ( elem[0] == "F4_Pkhp" ) {
                m_F4_Pkhp = boost::lexical_cast<double>(elem[1]);
            }
            else if ( elem[0] == "F5_Pkshp" ) {
                m_F5_Pkshp = boost::lexical_cast<double>(elem[1]);
            }
            else if ( elem[0] == "F6_Pthp" ) {
                m_F6_Pthp = boost::lexical_cast<double>(elem[1]);
            }
            else if ( elem[0] == "F7_Ptlp" ) {
                m_F7_Ptlp = boost::lexical_cast<double>(elem[1]);
            }
            else if ( elem[0] == "F8_Pr" ) {
                m_F8_Pr = boost::lexical_cast<double>(elem[1]);
            }
            else if ( elem[0] == "sysNum" ) {
                m_sysNum = boost::lexical_cast<double>(elem[1]);
            }
            else if ( elem[0] == "pipeNumHpOut" ) {
                m_pipeNumHpOut = boost::lexical_cast<double>(elem[1]);
            }
            else if ( elem[0] == "pipeNumHpIn" ) {
                m_pipeNumHpIn = boost::lexical_cast<double>(elem[1]);
            }
        }

        s.clear();
        elem.clear();
    }

    fin.close();
}

bool Configuration::createBlank() const {

    ofstream fout(CONFIGFILE);

    if ( !fout ) {
        cout << ERRORMSGBLANK << "Can not open file \"" << CONFIGFILE << "\" to write!\n";
        return false;
    }

    fout << "//\n"
         << "// This is " << Identification{}.name() << " configuration file.\n"
         << "// Parameter-Value delimiter is symbol \"" << PARAMDELIMITER << "\".\n"
         << "// Text after \"//\" is comment.\n"
         << "//\n\n";

    fout << "// NOTE: In case of single stage turbocharging results will be in HP section.\n\n";

    fout << "// Engine description\n"
         << "testObjDescr" << PARAMDELIMITER << m_testObjDescr << "\n\n"
         << "// Aftercooler type (low pressure). 0 - air-air, 1 - coolant-air\n"
         << "acTypelp" << PARAMDELIMITER << m_acType_lp << "\n\n"
         << "// Aftercooler type (high pressure). 0 - air-air, 1 - coolant-air\n"
         << "acTypehp" << PARAMDELIMITER << m_acType_hp << "\n\n"
         << "// Standard barometric pressure, kPa\n"
         << "B0_std" << PARAMDELIMITER << m_B0_std << "\n\n"
         << "// Standard inlet temperature, degC\n"
         << "T0_std" << PARAMDELIMITER << m_T0_std << "\n\n"
         << "// Engine displacement, m3\n"
         << "Vh" << PARAMDELIMITER << m_Vh << "\n\n"
         << "// Sectional area in measurement point of S parameter, m2\n"
         << "F1_S" << PARAMDELIMITER << m_F1_S << "\n\n"
         << "// Sectional area in measurement point of Pklp parameter, m2\n"
         << "F2_Pklp" << PARAMDELIMITER << m_F2_Pklp << "\n\n"
         << "// Sectional area in measurement point of Pkslp parameter, m2\n"
         << "F3_Pkslp" << PARAMDELIMITER << m_F3_Pkslp << "\n\n"
         << "// Sectional area in measurement point of Pkhp parameter, m2\n"
         << "F4_Pkhp" << PARAMDELIMITER << m_F4_Pkhp << "\n\n"
         << "// Sectional area in measurement point of Pkshp parameter, m2\n"
         << "F5_Pkshp" << PARAMDELIMITER << m_F5_Pkshp << "\n\n"
         << "// Sectional area in measurement point of Pthp parameter, m2\n"
         << "F6_Pthp" << PARAMDELIMITER << m_F6_Pthp << "\n\n"
         << "// Sectional area in measurement point of Ptlp parameter, m2\n"
         << "F7_Ptlp" << PARAMDELIMITER << m_F7_Ptlp << "\n\n"
         << "// Sectional area in measurement point of Pr parameter, m2\n"
         << "F8_Pr" << PARAMDELIMITER << m_F8_Pr << "\n\n"
         << "// Number of engine charging systems\n"
         << "sysNum" << PARAMDELIMITER << m_sysNum << "\n\n"
         << "// Number of out pipes of high pressure (compressor)\n"
         << "pipeNumHpOut" << PARAMDELIMITER << m_pipeNumHpOut << "\n\n"
         << "// Number of in pipes of high pressure (turbine)\n"
         << "pipeNumHpIn" << PARAMDELIMITER << m_pipeNumHpIn << "\n\n";

    fout.close();

    return true;
}
