/*
    tkr
    Calculation of turbocharger parameters.

    File: tkrparameters.cpp

    Copyright (C) 2014 Artem Petrov <pa2311@gmail.com>, Boris R. Blankshtein

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

#include "tkrparameters.hpp"
#include "constants.hpp"
#include "configuration.hpp"
#include "auxfunctions.hpp"
#include "identification.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cmath>
#include <fstream>
#include <ctime>
#include <iomanip>

#define BOOST_NO_CXX11_SCOPED_ENUMS

#include <boost/lexical_cast.hpp>

using std::cout;
using std::string;
using std::vector;
using std::shared_ptr;
using std::ofstream;
using std::setprecision;
using std::fixed;

TkrParameters::TkrParameters(const shared_ptr<Configuration> &cfg) {
    m_conf = cfg;
}

bool TkrParameters::calculate(const vector< vector<double> > &v) {

    if ( v.empty() ) {
        return false;
    }

    prepareArrays(v);
    preCalculate();
    doCalculate();

    return true;
}

void TkrParameters::prepareArrays(const vector< vector<double> > &v) {

    m_n = v.size();

    ma_n.resize(m_n);
    ma_Me.resize(m_n);
    ma_Ne.resize(m_n);
    ma_Gfuel.resize(m_n);
    ma_Gair.resize(m_n);
    ma_B0.resize(m_n);
    ma_S.resize(m_n);
    ma_Pk_lp.resize(m_n);
    ma_Pks_lp.resize(m_n);
    ma_Pk_hp.resize(m_n);
    ma_Pks_hp.resize(m_n);
    ma_Pt_hp.resize(m_n);
    ma_Pt_lp.resize(m_n);
    ma_Pr.resize(m_n);
    ma_T0.resize(m_n);
    ma_Tk_lp.resize(m_n);
    ma_Tks_lp.resize(m_n);
    ma_Tk_hp.resize(m_n);
    ma_Tks_hp.resize(m_n);
    ma_Tt_hp.resize(m_n);
    ma_Tt_lp.resize(m_n);
    ma_Tr.resize(m_n);
    ma_Tcool.resize(m_n);

    for ( size_t i=0; i<v.size(); i++ ) {

        ma_n     [i] = v[i][0];
        ma_Me    [i] = v[i][1];
        ma_Ne    [i] = v[i][2];
        ma_Gfuel [i] = v[i][3];
        ma_Gair  [i] = v[i][4];
        ma_B0    [i] = v[i][5];
        ma_S     [i] = v[i][6];
        ma_Pk_lp [i] = v[i][7];
        ma_Pks_lp[i] = v[i][8];
        ma_Pk_hp [i] = v[i][9];
        ma_Pks_hp[i] = v[i][10];
        ma_Pt_hp [i] = v[i][11];
        ma_Pt_lp [i] = v[i][12];
        ma_Pr    [i] = v[i][13];
        ma_T0    [i] = v[i][14];
        ma_Tk_lp [i] = v[i][15];
        ma_Tks_lp[i] = v[i][16];
        ma_Tk_hp [i] = v[i][17];
        ma_Tks_hp[i] = v[i][18];
        ma_Tt_hp [i] = v[i][19];
        ma_Tt_lp [i] = v[i][20];
        ma_Tr    [i] = v[i][21];
        ma_Tcool [i] = v[i][22];
    }

    ma_B0_r.resize(m_n);
    ma_S_r.resize(m_n);
    ma_Pk_lp_r.resize(m_n);
    ma_Pks_lp_r.resize(m_n);
    ma_Pk_hp_r.resize(m_n);
    ma_Pks_hp_r.resize(m_n);
    ma_Pt_hp_r.resize(m_n);
    ma_Pt_lp_r.resize(m_n);
    ma_Pr_r.resize(m_n);
    ma_T0_r.resize(m_n);
    ma_Tk_lp_r.resize(m_n);
    ma_Tks_lp_r.resize(m_n);
    ma_Tk_hp_r.resize(m_n);
    ma_Tks_hp_r.resize(m_n);
    ma_Tt_hp_r.resize(m_n);
    ma_Tt_lp_r.resize(m_n);
    ma_Tr_r.resize(m_n);
    ma_Tcool_r.resize(m_n);

    ma_Gair_real.resize(m_n);
    ma_Gexh_real.resize(m_n);

    ma_Y_S_r.resize(m_n);
    ma_Y_Pk_lp_r.resize(m_n);
    ma_Y_Pks_lp_r.resize(m_n);
    ma_Y_Pk_hp_r.resize(m_n);
    ma_Y_Pks_hp_r.resize(m_n);
    ma_Y_Pt_hp_r.resize(m_n);
    ma_Y_Pt_lp_r.resize(m_n);
    ma_Y_Pr_r.resize(m_n);

    ma_Lambda_S_r.resize(m_n);
    ma_Lambda_Pk_lp_r.resize(m_n);
    ma_Lambda_Pks_lp_r.resize(m_n);
    ma_Lambda_Pk_hp_r.resize(m_n);
    ma_Lambda_Pks_hp_r.resize(m_n);
    ma_Lambda_Pt_hp_r.resize(m_n);
    ma_Lambda_Pt_lp_r.resize(m_n);
    ma_Lambda_Pr_r.resize(m_n);

    ma_Pi_S_r.resize(m_n);
    ma_Pi_Pk_lp_r.resize(m_n);
    ma_Pi_Pks_lp_r.resize(m_n);
    ma_Pi_Pk_hp_r.resize(m_n);
    ma_Pi_Pks_hp_r.resize(m_n);
    ma_Pi_Pt_hp_r.resize(m_n);
    ma_Pi_Pt_lp_r.resize(m_n);
    ma_Pi_Pr_r.resize(m_n);

    ma_S_r_dyn.resize(m_n);
    ma_Pk_lp_r_dyn.resize(m_n);
    ma_Pks_lp_r_dyn.resize(m_n);
    ma_Pk_hp_r_dyn.resize(m_n);
    ma_Pks_hp_r_dyn.resize(m_n);
    ma_Pt_hp_r_dyn.resize(m_n);
    ma_Pt_lp_r_dyn.resize(m_n);
    ma_Pr_r_dyn.resize(m_n);

    ma_nuv.resize(m_n);
    ma_E1.resize(m_n);
    ma_E2.resize(m_n);

    ma_Gair_lp_r.resize(m_n);
    ma_Gair_hp_r.resize(m_n);
    ma_Pik_lp.resize(m_n);
    ma_Pik_hp.resize(m_n);
    ma_nuad_lp.resize(m_n);
    ma_nuad_hp.resize(m_n);
    ma_Ncomp_lp.resize(m_n);
    ma_Ncomp_hp.resize(m_n);

    ma_Gexh_lp_r.resize(m_n);
    ma_Gexh_hp_r.resize(m_n);
    ma_Pit_lp.resize(m_n);
    ma_Pit_hp.resize(m_n);
    ma_Tr_calc_lp.resize(m_n);
    ma_phi_lp.resize(m_n);
    ma_Tr_calc_hp.resize(m_n);
    ma_phi_hp.resize(m_n);
    ma_Nt_dis_lp.resize(m_n);
    ma_Nt_dis_hp.resize(m_n);
    ma_nute_lp.resize(m_n);
    ma_nute_hp.resize(m_n);
    ma_Cad_lp.resize(m_n);
    ma_rhog_lp.resize(m_n);
    ma_muft_lp.resize(m_n);
    ma_Cad_hp.resize(m_n);
    ma_rhog_hp.resize(m_n);
    ma_muft_hp.resize(m_n);
    ma_Ft_lp.resize(m_n);
    ma_Ft_hp.resize(m_n);

    ma_nutkr_lp.resize(m_n);
    ma_nutkr_hp.resize(m_n);
    ma_nusys.resize(m_n);
}

void TkrParameters::preCalculate() {

    for ( size_t i=0; i<m_n; i++ ) {

        ma_B0_r    [i] = ma_B0    [i] * 100.0;
        ma_S_r     [i] = ma_S     [i] + ma_B0_r[i];
        ma_Pk_lp_r [i] = ma_Pk_lp [i] * 100.0 + ma_B0_r[i];
        ma_Pks_lp_r[i] = ma_Pks_lp[i] * 100.0 + ma_B0_r[i];
        ma_Pk_hp_r [i] = ma_Pk_hp [i] * 100.0 + ma_B0_r[i];
        ma_Pks_hp_r[i] = ma_Pks_hp[i] * 100.0 + ma_B0_r[i];
        ma_Pt_hp_r [i] = ma_Pt_hp [i] * 100.0 + ma_B0_r[i];
        ma_Pt_lp_r [i] = ma_Pt_lp [i] * 100.0 + ma_B0_r[i];
        ma_Pr_r    [i] = ma_Pr    [i] + ma_B0_r[i];
        ma_T0_r    [i] = ma_T0    [i] + 273.0;
        ma_Tk_lp_r [i] = ma_Tk_lp [i] + 273.0;
        ma_Tks_lp_r[i] = ma_Tks_lp[i] + 273.0;
        ma_Tk_hp_r [i] = ma_Tk_hp [i] + 273.0;
        ma_Tks_hp_r[i] = ma_Tks_hp[i] + 273.0;
        ma_Tt_hp_r [i] = ma_Tt_hp [i] + 273.0;
        ma_Tt_lp_r [i] = ma_Tt_lp [i] + 273.0;
        ma_Tr_r    [i] = ma_Tr    [i] + 273.0;
        ma_Tcool_r [i] = ma_Tcool [i] + 273.0;
    }
}

void TkrParameters::doCalculate() {

    for ( size_t i=0; i<m_n; i++ ) {

        ma_Gair_real[i] = ma_Gair[i] / 3600.0;

        ma_Y_S_r[i] = ma_Gair_real[i] * sqrt(ma_T0_r[i]) / (ma_S_r[i] * m_conf->val_F1_S() * 20.317);
        ma_Y_Pk_lp_r[i] = ma_Gair_real[i] * sqrt(ma_Tk_lp_r[i]) / (ma_Pk_lp_r[i] * m_conf->val_F2_Pklp() * 20.317);
        ma_Y_Pks_lp_r[i] = ma_Gair_real[i] * sqrt(ma_Tks_lp_r[i]) / (ma_Pks_lp_r[i] * m_conf->val_F3_Pkslp() * 20.317);
        ma_Y_Pk_hp_r[i] = ma_Gair_real[i] * sqrt(ma_Tk_hp_r[i]) / (ma_Pk_hp_r[i] * m_conf->val_F4_Pkhp() * m_conf->val_pipeNumHpOut() * 20.317);
        ma_Y_Pks_hp_r[i] = ma_Gair_real[i] * sqrt(ma_Tks_hp_r[i]) / (ma_Pks_hp_r[i] * m_conf->val_F5_Pkshp() * m_conf->val_pipeNumHpOut() * 20.317);

        ma_Gexh_real[i] = (ma_Gair[i] + ma_Gfuel[i] / m_conf->val_sysNum()) / 3600;

        ma_Y_Pt_hp_r[i] = ma_Gexh_real[i] * sqrt(ma_Tt_hp_r[i]) / (ma_Pt_hp_r[i] * m_conf->val_F6_Pthp() * m_conf->val_pipeNumHpIn() * 25.639);
        ma_Y_Pt_lp_r[i] = ma_Gexh_real[i] * sqrt(ma_Tt_lp_r[i]) / (ma_Pt_lp_r[i] * m_conf->val_F7_Ptlp() * 25.639);
        ma_Y_Pr_r[i] = ma_Gexh_real[i] * sqrt(ma_Tr_r[i]) / (ma_Pr_r[i] * m_conf->val_F8_Pr() * 25.639);

        ma_Lambda_S_r[i] = (sqrt(4.0 * 0.16667 * pow(ma_Y_S_r[i], 2.0) + pow(1.57744, 2.0)) - 1.57744) / (2.0 * 0.16667 * ma_Y_S_r[i]);
        ma_Lambda_Pk_lp_r[i] = (sqrt(4.0 * 0.16667 * pow(ma_Y_Pk_lp_r[i], 2.0) + pow(1.57744, 2.0)) - 1.57744) / (2.0 * 0.16667 * ma_Y_Pk_lp_r[i]);
        ma_Lambda_Pks_lp_r[i] = (sqrt(4.0 * 0.16667 * pow(ma_Y_Pks_lp_r[i], 2.0) + pow(1.57744, 2.0)) - 1.57744) / (2.0 * 0.16667 * ma_Y_Pks_lp_r[i]);
        ma_Lambda_Pk_hp_r[i] = (sqrt(4.0 * 0.16667 * pow(ma_Y_Pk_hp_r[i], 2.0) + pow(1.57744, 2.0)) - 1.57744) / (2.0 * 0.16667 * ma_Y_Pk_hp_r[i]);
        ma_Lambda_Pks_hp_r[i] = (sqrt(4.0 * 0.16667 * pow(ma_Y_Pks_hp_r[i], 2.0) + pow(1.57744, 2.0)) - 1.57744) / (2.0 * 0.16667 * ma_Y_Pks_hp_r[i]);

        ma_Lambda_Pt_hp_r[i] = (sqrt(4.0 * 0.14894 * pow(ma_Y_Pt_hp_r[i], 2.0) + pow(1.58529, 2.0)) - 1.58529) / (2.0 * 0.14894 * ma_Y_Pt_hp_r[i]);
        ma_Lambda_Pt_lp_r[i] = (sqrt(4.0 * 0.14894 * pow(ma_Y_Pt_lp_r[i], 2.0) + pow(1.58529, 2.0)) - 1.58529) / (2.0 * 0.14894 * ma_Y_Pt_lp_r[i]);
        ma_Lambda_Pr_r[i] = (sqrt(4.0 * 0.14894 * pow(ma_Y_Pr_r[i], 2.0) + pow(1.58529, 2.0)) - 1.58529) / (2.0 * 0.14894 * ma_Y_Pr_r[i]);

        ma_Pi_S_r[i] = pow(1 - 0.16667 * pow(ma_Lambda_S_r[i], 2), 3.5);
        ma_Pi_Pk_lp_r[i] = pow(1 - 0.16667 * pow(ma_Lambda_Pk_lp_r[i], 2), 3.5);
        ma_Pi_Pks_lp_r[i] = pow(1 - 0.16667 * pow(ma_Lambda_Pks_lp_r[i], 2), 3.5);
        ma_Pi_Pk_hp_r[i] = pow(1 - 0.16667 * pow(ma_Lambda_Pk_hp_r[i], 2), 3.5);
        ma_Pi_Pks_hp_r[i] = pow(1 - 0.16667 * pow(ma_Lambda_Pks_hp_r[i], 2), 3.5);

        ma_Pi_Pt_hp_r[i] = pow(1 - 0.14894 * pow(ma_Lambda_Pt_hp_r[i], 2), 3.85714);
        ma_Pi_Pt_lp_r[i] = pow(1 - 0.14894 * pow(ma_Lambda_Pt_lp_r[i], 2), 3.85714);
        ma_Pi_Pr_r[i] = pow(1 - 0.14894 * pow(ma_Lambda_Pr_r[i], 2), 3.85714);

        ma_S_r_dyn[i] = ma_S_r[i] / ma_Pi_S_r[i];
        ma_Pk_lp_r_dyn[i] = ma_Pk_lp_r[i] / ma_Pi_Pk_lp_r[i];
        ma_Pks_lp_r_dyn[i] = ma_Pks_lp_r[i] / ma_Pi_Pks_lp_r[i];
        ma_Pk_hp_r_dyn[i] = ma_Pk_hp_r[i] / ma_Pi_Pk_hp_r[i];
        ma_Pks_hp_r_dyn[i] = ma_Pks_hp_r[i] / ma_Pi_Pks_hp_r[i];

        ma_Pt_hp_r_dyn[i] = ma_Pt_hp_r[i] / ma_Pi_Pt_hp_r[i];
        ma_Pt_lp_r_dyn[i] = ma_Pt_lp_r[i] / ma_Pi_Pt_lp_r[i];
        ma_Pr_r_dyn[i] = ma_Pr_r[i] / ma_Pi_Pr_r[i];

        ma_nuv[i] = 0.12 * ma_Gair_real[i] * 288.294 * ma_Tks_hp_r[i] / (m_conf->val_Vh() / m_conf->val_sysNum() * ma_n[i] * ma_Pks_hp_r_dyn[i]);

        if ( m_conf->val_acType_lp() == ACTYPE_AIRAIR ) {
            if ( ma_T0_r[i] < 303.0 ) {
                ma_E1[i] = (ma_Tk_lp_r[i] - ma_Tks_lp_r[i]) / (ma_Tk_lp_r[i] - 298.0);
            }
            else {
                ma_E1[i] = (ma_Tk_lp_r[i] - ma_Tks_lp_r[i]) / (ma_Tk_lp_r[i] - ma_T0_r[i]);
            }
        }
        else {
            ma_E1[i] = (ma_Tk_lp_r[i] - ma_Tks_lp_r[i]) / (ma_Tk_lp_r[i] - ma_Tcool_r[i]);
        }

        if ( ma_E1[i] > 1.0 ) {
            ma_E1[i] = 1.0;
        }

        if ( (ma_Tk_lp_r[i] < ma_Tks_lp_r[i]) && (ma_E1[i] > 0) ) {
            ma_E1[i] *= -1.0;
        }

        if ( m_conf->val_acType_hp() == ACTYPE_AIRAIR ) {
            if ( ma_T0_r[i] < 303.0 ) {
                ma_E2[i] = (ma_Tk_hp_r[i] - ma_Tks_hp_r[i]) / (ma_Tk_hp_r[i] - 298.0);
            }
            else {
                ma_E2[i] = (ma_Tk_hp_r[i] - ma_Tks_hp_r[i]) / (ma_Tk_hp_r[i] - ma_T0_r[i]);
            }
        }
        else {
            ma_E2[i] = (ma_Tk_hp_r[i] - ma_Tks_hp_r[i]) / (ma_Tk_hp_r[i] - ma_Tcool_r[i]);
        }

        if ( ma_E2[i] > 1.0 ) {
            ma_E2[i] = 1.0;
        }

        if ( (ma_Tk_hp_r[i] < ma_Tks_hp_r[i]) && (ma_E2[i] > 0) ) {
            ma_E2[i] *= -1.0;
        }

        ma_Gair_lp_r[i] = ma_Gair_real[i] * m_conf->val_B0_std() / ma_S_r_dyn[i] * pow(ma_T0_r[i] / (m_conf->val_T0_std() + 273), 0.5);
        ma_Gair_hp_r[i] = ma_Gair_real[i] * m_conf->val_B0_std() / ma_Pks_lp_r_dyn[i] * pow(ma_Tks_lp_r[i] / (m_conf->val_T0_std() + 273), 0.5);
        ma_Pik_lp[i] = ma_Pk_lp_r_dyn[i] / ma_S_r_dyn[i];
        ma_Pik_hp[i] = ma_Pk_hp_r_dyn[i] / ma_Pks_lp_r_dyn[i];
        ma_nuad_lp[i] = ma_T0_r[i] * (pow(ma_Pik_lp[i], 0.2857) - 1) / (ma_Tk_lp_r[i] - ma_T0_r[i]);
        ma_nuad_hp[i] = ma_Tks_lp_r[i] * (pow(ma_Pik_hp[i], 0.2857) - 1) / (ma_Tk_hp_r[i] - ma_Tks_lp_r[i]);
        ma_Ncomp_lp[i] = ma_Gair_real[i] * 1.009 * ma_T0_r[i] * (pow(ma_Pik_lp[i], 0.2857) - 1);
        ma_Ncomp_hp[i] = ma_Gair_real[i] * 1.009 * ma_Tks_lp_r[i] * (pow(ma_Pik_hp[i], 0.2857) - 1);

        ma_Pit_lp[i] = ma_Pt_lp_r_dyn[i] / ma_Pr_r_dyn[i];
        ma_Pit_hp[i] = ma_Pt_hp_r_dyn[i] / ma_Pt_lp_r_dyn[i];
        ma_Tr_calc_lp[i] = (ma_Tt_lp_r[i]) / pow(ma_Pit_lp[i], 0.2593);
        ma_phi_lp[i] = (ma_Tr_r[i] - ma_Tr_calc_lp[i]) / (ma_Tt_lp_r[i] - ma_Tr_calc_lp[i]);
        if ( ma_phi_lp[i] <= 0.04 ) {
            ma_phi_lp[i] = 0;
        }
        ma_Tr_calc_hp[i] = (ma_Tt_hp_r[i]) / pow(ma_Pit_hp[i], 0.2593);
        ma_phi_hp[i] = (ma_Tt_lp_r[i] - ma_Tr_calc_hp[i]) / (ma_Tt_hp_r[i] - ma_Tr_calc_hp[i]);
        if ( ma_phi_hp[i] <= 0.04 ) {
            ma_phi_hp[i] = 0;
        }
        ma_Gexh_lp_r[i] = ma_Gexh_real[i] * pow(ma_Tt_lp_r[i], 0.5) / ma_Pt_lp_r_dyn[i] * (1 - ma_phi_lp[i]);
        ma_Gexh_hp_r[i] = ma_Gexh_real[i] * pow(ma_Tt_hp_r[i], 0.5) / ma_Pt_hp_r_dyn[i] * (1 - ma_phi_hp[i]);
        ma_Nt_dis_lp[i] = ma_Gexh_real[i] * (1 - ma_phi_lp[i]) * 1.10892 * ma_Tt_lp_r[i] * (1 - 1 / pow(ma_Pit_lp[i], 0.2593));
        ma_Nt_dis_hp[i] = ma_Gexh_real[i] * (1 - ma_phi_hp[i]) * 1.10892 * ma_Tt_hp_r[i] * (1 - 1 / pow(ma_Pit_hp[i], 0.2593));
        ma_nute_lp[i] = (ma_Ncomp_lp[i] * 0.95) / (ma_Nt_dis_lp[i] * ma_nuad_lp[i]);
        ma_nute_hp[i] = (ma_Ncomp_hp[i] * 0.95) / (ma_Nt_dis_hp[i] * ma_nuad_hp[i]);
        ma_Cad_lp[i] = pow(2000 * ma_Nt_dis_lp[i] / ma_Gexh_real[i] / (1 - ma_phi_lp[i]), 0.5);
        ma_rhog_lp[i] = ma_Pr_r[i] * 1000.0 / 287.497 / ma_Tr_r[i];
        ma_muft_lp[i] = ma_Gexh_real[i] * (1 - ma_phi_lp[i]) / ma_rhog_lp[i] / ma_Cad_lp[i] * 10000.0;
        ma_Cad_hp[i] = pow(2000 * ma_Nt_dis_hp[i] / ma_Gexh_real[i] / (1 - ma_phi_hp[i]), 0.5);
        ma_rhog_hp[i] = ma_Pt_lp_r[i] * 1000.0 / 287.497 / ma_Tt_lp_r[i];
        ma_muft_hp[i] = ma_Gexh_real[i] * (1 - ma_phi_hp[i]) / ma_rhog_hp[i] / ma_Cad_hp[i] * 10000.0;

        double tmp_Ft = 5.0;
        size_t iter = 0;

        while ( 1 ) {

            if ( iter > MAXITER ) {
                break;
            }

            double tmp_Ft_1 = ma_muft_lp[i] / (0.421189 * log(ma_Pit_lp[i]) + 0.707889) / muPit2(tmp_Ft);
            tmp_Ft = tmp_Ft_1;
            double tmp_Ft_2 = ma_muft_lp[i] / (0.421189 * log(ma_Pit_lp[i]) + 0.707889) / muPit2(tmp_Ft);
            tmp_Ft = tmp_Ft_2;

            if ( fabs(tmp_Ft_1 - tmp_Ft_2) <= FTDEFACCUR ) {
                ma_Ft_lp[i] = tmp_Ft_2;
                break;
            }

            iter++;
        }

        tmp_Ft = 5.0;
        iter = 0;

        while ( 1 ) {

            if ( iter > MAXITER ) {
                break;
            }

            double tmp_Ft_1 = ma_muft_hp[i] / (0.421189 * log(ma_Pit_hp[i]) + 0.707889) / muPit2(tmp_Ft);
            tmp_Ft = tmp_Ft_1;
            double tmp_Ft_2 = ma_muft_hp[i] / (0.421189 * log(ma_Pit_hp[i]) + 0.707889) / muPit2(tmp_Ft);
            tmp_Ft = tmp_Ft_2;

            if ( fabs(tmp_Ft_1 - tmp_Ft_2) <= FTDEFACCUR ) {
                ma_Ft_hp[i] = tmp_Ft_2;
                break;
            }

            iter++;
        }

        ma_nutkr_lp[i] = ma_nuad_lp[i] * ma_nute_lp[i];
        ma_nutkr_hp[i] = ma_nuad_hp[i] * ma_nute_hp[i];

        ma_nusys[i] = ma_nutkr_lp[i] * ma_nutkr_hp[i];
    }

    cout << MSGBLANK << "Calculation completed.\n";
}

double TkrParameters::muPit2(double Ft) const {

    if ( Ft < 5.0 ) {
        return 0.895;
    }
    else if ( (Ft >= 5.0) && (Ft <= 55.0) ) {
        return 0.87503 + 0.0250807 * Ft
            - 0.00546323        * pow(Ft, 2)
            + 0.000278903       * pow(Ft, 3)
            - 0.00000655348     * pow(Ft, 4)
            + 0.0000000737792   * pow(Ft, 5)
            - 0.000000000320939 * pow(Ft, 6);
    }
    else {
        return 0.410;
    }
}

bool TkrParameters::createReport() {

    time_t t = time(NULL);
    struct tm *dtnow = localtime(&t);

    string year = boost::lexical_cast<string>(dtnow->tm_year + 1900);
    string mon  = boost::lexical_cast<string>(dtnow->tm_mon + 1);
    string day  = boost::lexical_cast<string>(dtnow->tm_mday);
    string hour = boost::lexical_cast<string>(dtnow->tm_hour);
    string min  = boost::lexical_cast<string>(dtnow->tm_min);
    string sec  = boost::lexical_cast<string>(dtnow->tm_sec);

    string currDateTime(year + "-" + trimDate(mon) + "-" + trimDate(day) + "_" + trimDate(hour) + "-" + trimDate(min) + "-" + trimDate(sec));
    string reportName(REPORTNAME);
    string reportFileName = reportName + "__" + currDateTime + ".csv";

    ofstream fout(reportFileName);

    if ( !fout ) {
        cout << ERRORMSGBLANK << "Can not open file \"" << reportFileName << "\" to write!\n";
        return false;
    }

    fout << Identification{}.name() << " v" << Identification{}.version() << "\n\n"
         << "Engine description: " << m_conf->val_testObjDescr() << "\n\n"
         << "Standard conditions\n\n"
         << "B0_std" << CSVDELIMETER << m_conf->val_B0_std() << CSVDELIMETER << "kPa\n"
         << "T0_std" << CSVDELIMETER << m_conf->val_T0_std() << CSVDELIMETER << "degC\n\n"
         << "Source data\n\n"
         << "Vh" << CSVDELIMETER << m_conf->val_Vh() << CSVDELIMETER << "m3\n"
         << "F1_S" << CSVDELIMETER << m_conf->val_F1_S() << CSVDELIMETER << "m2\n"
         << "F2_Pk_lp" << CSVDELIMETER << m_conf->val_F2_Pklp() << CSVDELIMETER << "m2\n"
         << "F3_Pks_lp" << CSVDELIMETER << m_conf->val_F3_Pkslp() << CSVDELIMETER << "m2\n"
         << "F4_Pk_hp" << CSVDELIMETER << m_conf->val_F4_Pkhp() << CSVDELIMETER << "m2\n"
         << "F5_Pks_hp" << CSVDELIMETER << m_conf->val_F5_Pkshp() << CSVDELIMETER << "m2\n"
         << "F6_Pt_hp" << CSVDELIMETER << m_conf->val_F6_Pthp() << CSVDELIMETER << "m2\n"
         << "F7_Pt_lp" << CSVDELIMETER << m_conf->val_F7_Ptlp() << CSVDELIMETER << "m2\n"
         << "F8_Pr" << CSVDELIMETER << m_conf->val_F8_Pr() << CSVDELIMETER << "m2\n"
         << "sysNum" << CSVDELIMETER << m_conf->val_sysNum() << CSVDELIMETER << "\n"
         << "pipeNumHpOut" << CSVDELIMETER << m_conf->val_pipeNumHpOut() << CSVDELIMETER << "\n"
         << "pipeNumHpIn" << CSVDELIMETER << m_conf->val_pipeNumHpIn() << CSVDELIMETER << "\n"
         << "Aftercooler type (low pressure)" << CSVDELIMETER << m_conf->val_acType_lp() << "\n"
         << "Aftercooler type (high pressure)" << CSVDELIMETER << m_conf->val_acType_hp() << "\n\n";

    for ( size_t i=0; i<colCaptions.size(); i++ ) {

        fout << colCaptions[i];

        if ( i == (colCaptions.size()-1) ) {
            fout << "\n";
        }
        else {
            fout << CSVDELIMETER;
        }
    }

    for ( size_t i=0; i<m_n; i++ ) {

        fout << ma_n[i]      << CSVDELIMETER
             << ma_Me[i]     << CSVDELIMETER
             << ma_Ne[i]     << CSVDELIMETER
             << ma_Gfuel[i]  << CSVDELIMETER
             << ma_Gair[i]   << CSVDELIMETER
             << ma_B0[i]     << CSVDELIMETER
             << ma_S[i]      << CSVDELIMETER
             << ma_Pk_lp[i]  << CSVDELIMETER
             << ma_Pks_lp[i] << CSVDELIMETER
             << ma_Pk_hp[i]  << CSVDELIMETER
             << ma_Pks_hp[i] << CSVDELIMETER
             << ma_Pt_hp[i]  << CSVDELIMETER
             << ma_Pt_lp[i]  << CSVDELIMETER
             << ma_Pr[i]     << CSVDELIMETER
             << ma_T0[i]     << CSVDELIMETER
             << ma_Tk_lp[i]  << CSVDELIMETER
             << ma_Tks_lp[i] << CSVDELIMETER
             << ma_Tk_hp[i]  << CSVDELIMETER
             << ma_Tks_hp[i] << CSVDELIMETER
             << ma_Tt_hp[i]  << CSVDELIMETER
             << ma_Tt_lp[i]  << CSVDELIMETER
             << ma_Tr[i]     << CSVDELIMETER
             << ma_Tcool[i]  << CSVDELIMETER
             << "\n";
    }

    fout << "\n" << "Calculation results\n\n"
         << "n[min-1]"          << CSVDELIMETER
         << "Me[Nm]"            << CSVDELIMETER
         << "Ne[kW]"            << CSVDELIMETER
         << "Gair/Gfuel[-]"     << CSVDELIMETER
         << "nuv[-]"            << CSVDELIMETER
         << "E1[-]"             << CSVDELIMETER
         << "E2[-]"             << CSVDELIMETER << CSVDELIMETER
         << "Gair_lp_r[kg/s]"   << CSVDELIMETER
         << "Pik_lp[-]"         << CSVDELIMETER
         << "nuad_lp[-]"        << CSVDELIMETER
         << "Ncomp_lp[kW]"      << CSVDELIMETER << CSVDELIMETER
         << "Gexh_lp_r[(kg/s)*sqrt(K)/kPa]" << CSVDELIMETER
         << "Pit_lp[-]"         << CSVDELIMETER
         << "nute_lp[-]"        << CSVDELIMETER
         << "muft_lp[cm2]"      << CSVDELIMETER
         << "Nt_dis_lp[kW]"     << CSVDELIMETER
         << "phi_lp[-]"         << CSVDELIMETER
         << "Ft_lp[cm2]"        << CSVDELIMETER << CSVDELIMETER
         << "Gair_hp_r[kg/s]"   << CSVDELIMETER
         << "Pik_hp[-]"         << CSVDELIMETER
         << "nuad_hp[-]"        << CSVDELIMETER
         << "Ncomp_hp[kW]"      << CSVDELIMETER << CSVDELIMETER
         << "Gexh_hp_r[(kg/s)*sqrt(K)/kPa]" << CSVDELIMETER
         << "Pit_hp[-]"         << CSVDELIMETER
         << "nute_hp[-]"        << CSVDELIMETER
         << "muft_hp[cm2]"      << CSVDELIMETER
         << "Nt_dis_hp[kW]"     << CSVDELIMETER
         << "phi_hp[-]"         << CSVDELIMETER
         << "Ft_hp[cm2]"        << CSVDELIMETER << CSVDELIMETER
         << "nu_tkr_lp[-]"      << CSVDELIMETER
         << "nu_tkr_hp[-]"      << CSVDELIMETER
         << "nu_sys[-]"         << CSVDELIMETER << CSVDELIMETER
         << "B0_r[kPa]"         << CSVDELIMETER
         << "S_r[kPa]"          << CSVDELIMETER
         << "Pk_lp_r[kPa]"      << CSVDELIMETER
         << "Pks_lp_r[kPa]"     << CSVDELIMETER
         << "Pk_hp_r[kPa]"      << CSVDELIMETER
         << "Pks_hp_r[kPa]"     << CSVDELIMETER
         << "Pt_hp_r[kPa]"      << CSVDELIMETER
         << "Pt_lp_r[kPa]"      << CSVDELIMETER
         << "Pr_r[kPa]"         << CSVDELIMETER << CSVDELIMETER
         << "S_r_dyn[kPa]"      << CSVDELIMETER
         << "Pk_lp_r_dyn[kPa]"  << CSVDELIMETER
         << "Pks_lp_r_dyn[kPa]" << CSVDELIMETER
         << "Pk_hp_r_dyn[kPa]"  << CSVDELIMETER
         << "Pks_hp_r_dyn[kPa]" << CSVDELIMETER
         << "Pt_hp_r_dyn[kPa]"  << CSVDELIMETER
         << "Pt_lp_r_dyn[kPa]"  << CSVDELIMETER
         << "Pr_r_dyn[kPa]"     << CSVDELIMETER  << CSVDELIMETER
         << "T0_r[K]"           << CSVDELIMETER
         << "Tk_lp_r[K]"        << CSVDELIMETER
         << "Tks_lp_r[K]"       << CSVDELIMETER
         << "Tk_hp_r[K]"        << CSVDELIMETER
         << "Tks_hp_r[K]"       << CSVDELIMETER
         << "Tt_hp_r[K]"        << CSVDELIMETER
         << "Tt_lp_r[K]"        << CSVDELIMETER
         << "Tr_r[K]"           << "\n";

    for ( size_t i=0; i<m_n; i++ ) {

        fout << fixed << setprecision(0) << ma_n[i]  << CSVDELIMETER
             << fixed << setprecision(0) << ma_Me[i] << CSVDELIMETER
             << fixed << setprecision(2) << ma_Ne[i] << CSVDELIMETER
             << fixed << setprecision(2) << ma_Gair[i] / (ma_Gfuel[i] / m_conf->val_sysNum()) << CSVDELIMETER
             << fixed << setprecision(3) << ma_nuv[i]          << CSVDELIMETER
             << fixed << setprecision(3) << ma_E1[i]           << CSVDELIMETER
             << fixed << setprecision(3) << ma_E2[i]           << CSVDELIMETER << CSVDELIMETER
             << fixed << setprecision(3) << ma_Gair_lp_r[i]    << CSVDELIMETER
             << fixed << setprecision(3) << ma_Pik_lp[i]       << CSVDELIMETER
             << fixed << setprecision(3) << ma_nuad_lp[i]      << CSVDELIMETER
             << fixed << setprecision(2) << ma_Ncomp_lp[i]     << CSVDELIMETER << CSVDELIMETER
             << fixed << setprecision(3) << ma_Gexh_lp_r[i]    << CSVDELIMETER
             << fixed << setprecision(3) << ma_Pit_lp[i]       << CSVDELIMETER
             << fixed << setprecision(3) << ma_nute_lp[i]      << CSVDELIMETER
             << fixed << setprecision(1) << ma_muft_lp[i]      << CSVDELIMETER
             << fixed << setprecision(2) << ma_Nt_dis_lp[i]    << CSVDELIMETER
             << fixed << setprecision(3) << ma_phi_lp[i]       << CSVDELIMETER
             << fixed << setprecision(1) << ma_Ft_lp[i]        << CSVDELIMETER << CSVDELIMETER
             << fixed << setprecision(3) << ma_Gair_hp_r[i]    << CSVDELIMETER
             << fixed << setprecision(3) << ma_Pik_hp[i]       << CSVDELIMETER
             << fixed << setprecision(3) << ma_nuad_hp[i]      << CSVDELIMETER
             << fixed << setprecision(2) << ma_Ncomp_hp[i]     << CSVDELIMETER << CSVDELIMETER
             << fixed << setprecision(3) << ma_Gexh_hp_r[i]    << CSVDELIMETER
             << fixed << setprecision(3) << ma_Pit_hp[i]       << CSVDELIMETER
             << fixed << setprecision(3) << ma_nute_hp[i]      << CSVDELIMETER
             << fixed << setprecision(1) << ma_muft_hp[i]      << CSVDELIMETER
             << fixed << setprecision(2) << ma_Nt_dis_hp[i]    << CSVDELIMETER
             << fixed << setprecision(3) << ma_phi_hp[i]       << CSVDELIMETER
             << fixed << setprecision(1) << ma_Ft_hp[i]        << CSVDELIMETER << CSVDELIMETER
             << fixed << setprecision(3) << ma_nutkr_lp[i]     << CSVDELIMETER
             << fixed << setprecision(3) << ma_nutkr_hp[i]     << CSVDELIMETER
             << fixed << setprecision(3) << ma_nusys[i]        << CSVDELIMETER << CSVDELIMETER
             << fixed << setprecision(1) << ma_B0_r[i]         << CSVDELIMETER
             << fixed << setprecision(1) << ma_S_r[i]          << CSVDELIMETER
             << fixed << setprecision(1) << ma_Pk_lp_r[i]      << CSVDELIMETER
             << fixed << setprecision(1) << ma_Pks_lp_r[i]     << CSVDELIMETER
             << fixed << setprecision(1) << ma_Pk_hp_r[i]      << CSVDELIMETER
             << fixed << setprecision(1) << ma_Pks_hp_r[i]     << CSVDELIMETER
             << fixed << setprecision(1) << ma_Pt_hp_r[i]      << CSVDELIMETER
             << fixed << setprecision(1) << ma_Pt_lp_r[i]      << CSVDELIMETER
             << fixed << setprecision(1) << ma_Pr_r[i]         << CSVDELIMETER << CSVDELIMETER
             << fixed << setprecision(1) << ma_S_r_dyn[i]      << CSVDELIMETER
             << fixed << setprecision(1) << ma_Pk_lp_r_dyn[i]  << CSVDELIMETER
             << fixed << setprecision(1) << ma_Pks_lp_r_dyn[i] << CSVDELIMETER
             << fixed << setprecision(1) << ma_Pk_hp_r_dyn[i]  << CSVDELIMETER
             << fixed << setprecision(1) << ma_Pks_hp_r_dyn[i] << CSVDELIMETER
             << fixed << setprecision(1) << ma_Pt_hp_r_dyn[i]  << CSVDELIMETER
             << fixed << setprecision(1) << ma_Pt_lp_r_dyn[i]  << CSVDELIMETER
             << fixed << setprecision(1) << ma_Pr_r_dyn[i]     << CSVDELIMETER << CSVDELIMETER
             << fixed << setprecision(1) << ma_T0_r[i]         << CSVDELIMETER
             << fixed << setprecision(1) << ma_Tk_lp_r[i]      << CSVDELIMETER
             << fixed << setprecision(1) << ma_Tks_lp_r[i]     << CSVDELIMETER
             << fixed << setprecision(1) << ma_Tk_hp_r[i]      << CSVDELIMETER
             << fixed << setprecision(1) << ma_Tks_hp_r[i]     << CSVDELIMETER
             << fixed << setprecision(1) << ma_Tt_hp_r[i]      << CSVDELIMETER
             << fixed << setprecision(1) << ma_Tt_lp_r[i]      << CSVDELIMETER
             << fixed << setprecision(1) << ma_Tr_r[i]         << "\n";
    }
/*
    fout << "\n" << "Checkout data\n\n"
         << "Gair_real[kg/s]"    << CSVDELIMETER
         << "Gexh_real[kg/s]"    << CSVDELIMETER << CSVDELIMETER
         << "Y_S_r[-]"           << CSVDELIMETER
         << "Y_Pk_lp_r[-]"       << CSVDELIMETER
         << "Y_Pks_lp_r[-]"      << CSVDELIMETER
         << "Y_Pk_hp_r[-]"       << CSVDELIMETER
         << "Y_Pks_hp_r[-]"      << CSVDELIMETER
         << "Y_Pt_hp_r[-]"       << CSVDELIMETER
         << "Y_Pt_lp_r[-]"       << CSVDELIMETER
         << "Y_Pr_r[-]"          << CSVDELIMETER << CSVDELIMETER
         << "Lambda_S_r[-]"      << CSVDELIMETER
         << "Lambda_Pk_lp_r[-]"  << CSVDELIMETER
         << "Lambda_Pks_lp_r[-]" << CSVDELIMETER
         << "Lambda_Pk_hp_r[-]"  << CSVDELIMETER
         << "Lambda_Pks_hp_r[-]" << CSVDELIMETER
         << "Lambda_Pt_hp_r[-]"  << CSVDELIMETER
         << "Lambda_Pt_lp_r[-]"  << CSVDELIMETER
         << "Lambda_Pr_r[-]"     << CSVDELIMETER << CSVDELIMETER
         << "Pi_S_r[-]"          << CSVDELIMETER
         << "Pi_Pk_lp_r[-]"      << CSVDELIMETER
         << "Pi_Pks_lp_r[-]"     << CSVDELIMETER
         << "Pi_Pk_hp_r[-]"      << CSVDELIMETER
         << "Pi_Pks_hp_r[-]"     << CSVDELIMETER
         << "Pi_Pt_hp_r[-]"      << CSVDELIMETER
         << "Pi_Pt_lp_r[-]"      << CSVDELIMETER
         << "Pi_Pr_r[-]"         << CSVDELIMETER
         << "\n";

    for ( size_t i=0; i<m_n; i++ ) {

        fout << fixed << setprecision(3) << ma_Gair_real[i]        << CSVDELIMETER
             << fixed << setprecision(3) << ma_Gexh_real[i]        << CSVDELIMETER << CSVDELIMETER
             << fixed << setprecision(3) << ma_Y_S_r[i]            << CSVDELIMETER
             << fixed << setprecision(3) << ma_Y_Pk_lp_r[i]        << CSVDELIMETER
             << fixed << setprecision(3) << ma_Y_Pks_lp_r[i]       << CSVDELIMETER
             << fixed << setprecision(3) << ma_Y_Pk_hp_r[i]        << CSVDELIMETER
             << fixed << setprecision(3) << ma_Y_Pks_hp_r[i]       << CSVDELIMETER
             << fixed << setprecision(3) << ma_Y_Pt_hp_r[i]        << CSVDELIMETER
             << fixed << setprecision(3) << ma_Y_Pt_lp_r[i]        << CSVDELIMETER
             << fixed << setprecision(3) << ma_Y_Pr_r[i]           << CSVDELIMETER << CSVDELIMETER
             << fixed << setprecision(3) << ma_Lambda_S_r[i]       << CSVDELIMETER
             << fixed << setprecision(3) << ma_Lambda_Pk_lp_r[i]   << CSVDELIMETER
             << fixed << setprecision(3) << ma_Lambda_Pks_lp_r[i]  << CSVDELIMETER
             << fixed << setprecision(3) << ma_Lambda_Pk_hp_r[i]   << CSVDELIMETER
             << fixed << setprecision(3) << ma_Lambda_Pks_hp_r[i]  << CSVDELIMETER
             << fixed << setprecision(3) << ma_Lambda_Pt_hp_r[i]   << CSVDELIMETER
             << fixed << setprecision(3) << ma_Lambda_Pt_lp_r[i]   << CSVDELIMETER
             << fixed << setprecision(3) << ma_Lambda_Pr_r[i]      << CSVDELIMETER << CSVDELIMETER
             << fixed << setprecision(3) << ma_Pi_S_r[i]           << CSVDELIMETER
             << fixed << setprecision(3) << ma_Pi_Pk_lp_r[i]       << CSVDELIMETER
             << fixed << setprecision(3) << ma_Pi_Pks_lp_r[i]      << CSVDELIMETER
             << fixed << setprecision(3) << ma_Pi_Pk_hp_r[i]       << CSVDELIMETER
             << fixed << setprecision(3) << ma_Pi_Pks_hp_r[i]      << CSVDELIMETER
             << fixed << setprecision(3) << ma_Pi_Pt_hp_r[i]       << CSVDELIMETER
             << fixed << setprecision(3) << ma_Pi_Pt_lp_r[i]       << CSVDELIMETER
             << fixed << setprecision(3) << ma_Pi_Pr_r[i]          << CSVDELIMETER
             << "\n";
    }
*/
    fout.close();

    cout << MSGBLANK << "Report file \"" << reportFileName << "\"created.\n";

    return true;
}
