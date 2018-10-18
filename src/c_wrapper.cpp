/*
 *  This source code is part of MicroPP: a finite element library
 *  to solve microstructural problems for composite materials.
 *
 *  Copyright (C) - 2018 - Jimmy Aguilar Mena <kratsbinovish@gmail.com>
 *                         Guido Giuntoli <gagiuntoli@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#include "micro.hpp"
#include "micropp_c_wrapper.h"


#define MAT_NUM 2
static micropp<3>* micro3 = NULL;
static material_t *materials[MAT_NUM];


extern "C" {

	void micropp_C_material_create()
	{
		for(int i = 0; i < MAT_NUM; ++i)
			materials[i] = new material_t;
	}

	void micropp_C_material_set(int num_mat, double E, double nu, double Ka,
	                   			double Sy, int type)
	{
		materials[num_mat]->set(E, nu, Ka, Sy, type);
	}

	void micropp_C_material_print(int num_mat)
	{
		materials[num_mat]->print();
	}

	void micropp_C_create3(int ngp, int size[3], int type, double *params)
	{
		micro3 = new micropp<3>(ngp, size, type, params, *materials);
	}

	void micropp_C_set_strain3(int gp, double strain[6])
	{
	   	micro3->set_macro_strain(gp, strain);
	}

	void micropp_C_get_stress3(int gp, double stress[6])
	{
	   	micro3->get_macro_stress(gp, stress);
	}

	void micropp_C_get_ctan3(int gp, double ctan[36])
	{
	   	micro3->get_macro_ctan(gp, ctan);
	}

	void micropp_C_homogenize()
	{
	   	micro3->homogenize();
	}

	void micropp_C_destroy3()
	{
	   	delete micro3;
	}

	/*

	   void free3_(micropp<3> **in)
	   {
	   delete (*in);
	   }

	   void get_nl_flag3_(const micropp<3> **self, int *gp_id, int *nl_flag)
	   {
	   (*nl_flag) = (*self)->get_nl_flag(*gp_id);
	   }

	   void update_vars3_(micropp<3> **self)
	   {
	   (*self)->update_vars();
	   }

	   void output3_(micropp<3> **self, int *tstep, int *gp_id)
	   {
	   (*self)->output(*tstep, *gp_id);
	   }

	   void write_info_files3_(micropp<3> **self)
	   {
	   (*self)->write_info_files();
	   }

	   void write_convergence_file3_(micropp<3> **self, int *tstep, int *rank)
	   {
	   (*self)->write_convergence_file(*tstep, *rank);
	   }

	   void print_info3_(micropp<3> **self)
	   {
	   printf("ptr2 %p\n", self);
	   (*self)->print_info();
	   }
	   */

}