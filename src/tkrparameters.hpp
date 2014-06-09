/*
    tkr
    Calculation of turbocharger parameters.

    File: tkrparamenters.hpp

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

#ifndef TKRPARAMETERS_HPP
#define TKRPARAMETERS_HPP

#include <vector>
#include <memory>

#include "configuration.hpp"

class TkrParameters {

public:

    TkrParameters(const std::shared_ptr<Configuration> &conf);

    bool calculate(const std::vector< std::vector<double> > &);
    bool createReport();

private:

    void prepareArrays(const std::vector< std::vector<double> > &);
    void preCalculate();
    void doCalculate();
    double muPit2(double) const;

    std::shared_ptr<Configuration> m_conf;

    size_t m_n = 0;

    std::vector<double> ma_n;
    std::vector<double> ma_Me;
    std::vector<double> ma_Ne;
    std::vector<double> ma_Gfuel;
    std::vector<double> ma_Gair;
    std::vector<double> ma_B0;
    std::vector<double> ma_S;
    std::vector<double> ma_Pk_lp;
    std::vector<double> ma_Pks_lp;
    std::vector<double> ma_Pk_hp;
    std::vector<double> ma_Pks_hp;
    std::vector<double> ma_Pt_hp;
    std::vector<double> ma_Pt_lp;
    std::vector<double> ma_Pr;
    std::vector<double> ma_T0;
    std::vector<double> ma_Tk_lp;
    std::vector<double> ma_Tks_lp;
    std::vector<double> ma_Tk_hp;
    std::vector<double> ma_Tks_hp;
    std::vector<double> ma_Tt_hp;
    std::vector<double> ma_Tt_lp;
    std::vector<double> ma_Tr;
    std::vector<double> ma_Tcool;

    std::vector<double> ma_B0_r;
    std::vector<double> ma_S_r;
    std::vector<double> ma_Pk_lp_r;
    std::vector<double> ma_Pks_lp_r;
    std::vector<double> ma_Pk_hp_r;
    std::vector<double> ma_Pks_hp_r;
    std::vector<double> ma_Pt_hp_r;
    std::vector<double> ma_Pt_lp_r;
    std::vector<double> ma_Pr_r;
    std::vector<double> ma_T0_r;
    std::vector<double> ma_Tk_lp_r;
    std::vector<double> ma_Tks_lp_r;
    std::vector<double> ma_Tk_hp_r;
    std::vector<double> ma_Tks_hp_r;
    std::vector<double> ma_Tt_hp_r;
    std::vector<double> ma_Tt_lp_r;
    std::vector<double> ma_Tr_r;
    std::vector<double> ma_Tcool_r;

    std::vector<double> ma_Gair_real;
    std::vector<double> ma_Gexh_real;

    std::vector<double> ma_Y_S_r;
    std::vector<double> ma_Y_Pk_lp_r;
    std::vector<double> ma_Y_Pks_lp_r;
    std::vector<double> ma_Y_Pk_hp_r;
    std::vector<double> ma_Y_Pks_hp_r;
    std::vector<double> ma_Y_Pt_hp_r;
    std::vector<double> ma_Y_Pt_lp_r;
    std::vector<double> ma_Y_Pr_r;

    std::vector<double> ma_Lambda_S_r;
    std::vector<double> ma_Lambda_Pk_lp_r;
    std::vector<double> ma_Lambda_Pks_lp_r;
    std::vector<double> ma_Lambda_Pk_hp_r;
    std::vector<double> ma_Lambda_Pks_hp_r;
    std::vector<double> ma_Lambda_Pt_hp_r;
    std::vector<double> ma_Lambda_Pt_lp_r;
    std::vector<double> ma_Lambda_Pr_r;

    std::vector<double> ma_Pi_S_r;
    std::vector<double> ma_Pi_Pk_lp_r;
    std::vector<double> ma_Pi_Pks_lp_r;
    std::vector<double> ma_Pi_Pk_hp_r;
    std::vector<double> ma_Pi_Pks_hp_r;
    std::vector<double> ma_Pi_Pt_hp_r;
    std::vector<double> ma_Pi_Pt_lp_r;
    std::vector<double> ma_Pi_Pr_r;

    std::vector<double> ma_S_r_dyn;
    std::vector<double> ma_Pk_lp_r_dyn;
    std::vector<double> ma_Pks_lp_r_dyn;
    std::vector<double> ma_Pk_hp_r_dyn;
    std::vector<double> ma_Pks_hp_r_dyn;
    std::vector<double> ma_Pt_hp_r_dyn;
    std::vector<double> ma_Pt_lp_r_dyn;
    std::vector<double> ma_Pr_r_dyn;

    std::vector<double> ma_nuv;
    std::vector<double> ma_E1;
    std::vector<double> ma_E2;

    std::vector<double> ma_Gair_lp_r;
    std::vector<double> ma_Gair_hp_r;
    std::vector<double> ma_Pik_lp;
    std::vector<double> ma_Pik_hp;
    std::vector<double> ma_nuad_lp;
    std::vector<double> ma_nuad_hp;
    std::vector<double> ma_Ncomp_lp;
    std::vector<double> ma_Ncomp_hp;

    std::vector<double> ma_Gexh_lp_r;
    std::vector<double> ma_Gexh_hp_r;
    std::vector<double> ma_Pit_lp;
    std::vector<double> ma_Pit_hp;
    std::vector<double> ma_Tr_calc_lp;
    std::vector<double> ma_phi_lp;
    std::vector<double> ma_Tr_calc_hp;
    std::vector<double> ma_phi_hp;
    std::vector<double> ma_Nt_dis_lp;
    std::vector<double> ma_Nt_dis_hp;
    std::vector<double> ma_nute_lp;
    std::vector<double> ma_nute_hp;
    std::vector<double> ma_Cad_lp;
    std::vector<double> ma_rhog_lp;
    std::vector<double> ma_muft_lp;
    std::vector<double> ma_Cad_hp;
    std::vector<double> ma_rhog_hp;
    std::vector<double> ma_muft_hp;
    std::vector<double> ma_Ft_lp;
    std::vector<double> ma_Ft_hp;

    std::vector<double> ma_nutkr_lp;
    std::vector<double> ma_nutkr_hp;
    std::vector<double> ma_nusys;

};

#endif // TKRPARAMETERS_HPP
