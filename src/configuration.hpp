/*
    tkr
    Calculation of turbocharger parameters.

    File: configuration.hpp

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

#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <string>

class Configuration {

public:

    Configuration();

    void readConfigFile();

    std::string val_testObjDescr() const {
        return m_testObjDescr;
    }
    size_t val_acType_lp() const {
        return m_acType_lp;
    }
    size_t val_acType_hp() const {
        return m_acType_hp;
    }
    double val_B0_std() const {
        return m_B0_std;
    }
    double val_T0_std() const {
        return m_T0_std;
    }
    double val_Vh() const {
        return m_Vh;
    }
    double val_F1_S() const {
        return m_F1_S;
    }
    double val_F2_Pklp() const {
        return m_F2_Pklp;
    }
    double val_F3_Pkslp() const {
        return m_F3_Pkslp;
    }
    double val_F4_Pkhp() const {
        return m_F4_Pkhp;
    }
    double val_F5_Pkshp() const {
        return m_F5_Pkshp;
    }
    double val_F6_Pthp() const {
        return m_F6_Pthp;
    }
    double val_F7_Ptlp() const {
        return m_F7_Ptlp;
    }
    double val_F8_Pr() const {
        return m_F8_Pr;
    }
    double val_sysNum() const {
        return m_sysNum;
    }
    double val_pipeNumHpOut() const {
        return m_pipeNumHpOut;
    }
    double val_pipeNumHpIn() const {
        return m_pipeNumHpIn;
    }

private:

    bool createBlank() const;

    std::string m_testObjDescr = "YMZ-......., TKR-.......";
    size_t m_acType_lp    = 0;        // aftercooler type
    size_t m_acType_hp    = 0;        // aftercooler type
    double m_B0_std       = 101.3;    // kPa
    double m_T0_std       = 20;       // degC
    double m_Vh           = 0.007014; // engine displacement, m3
    double m_F1_S         = 0.0177;   // sectional area in measurement point, m2
    double m_F2_Pklp      = 0.0058;   // sectional area in measurement point, m2
    double m_F3_Pkslp     = 0.0058;   // sectional area in measurement point, m2
    double m_F4_Pkhp      = 0.0042;   // sectional area in measurement point, m2
    double m_F5_Pkshp     = 0.0058;   // sectional area in measurement point, m2
    double m_F6_Pthp      = 0.0045;   // sectional area in measurement point, m2
    double m_F7_Ptlp      = 0.0050;   // sectional area in measurement point, m2
    double m_F8_Pr        = 0.0078;   // sectional area in measurement point, m2
    double m_sysNum       = 1;        // number of charging systems on the engine
    double m_pipeNumHpOut = 1;        // number of hp out pipes
    double m_pipeNumHpIn  = 1;        // number of hp in pipes
};

#endif // CONFIGURATION_HPP
