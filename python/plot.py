# Function plot 
#
#   Usage:
#   python3.6 plot.py -f setup.txt
#
#   Matheus J. Lazarotto (30/09/2020 -- 28/12/2020)

# Import auxiliary file
import sys
sys.path.append('../python')
from aux_par import *
from aux_plt import *

import os
import argparse

parser = argparse.ArgumentParser()
# Arg: file name with setups (function expressions, constant values, limits etc.)
parser.add_argument('-file', help = 'Setup file name',
                    action = 'store', dest = 'setup')
args = parser.parse_args()

# Setup file parse function
def parse_setup_data(flname, dic_dat):
    nFunctions = 0
    with open(flname, 'r') as inpt:
        for line in inpt:
            if line[0] == '#':
                continue
            elif 'f = ' in line or 'f=' in line or 'f =' in line or 'f= ' in line:
                nFunctions += 1
            elif 'x_min' in line:
                dic_dat['x_min'] = float(line.split('=')[1])
            elif 'x_max' in line:
                dic_dat['x_max'] = float(line.split('=')[1])
            elif 'y_min' in line:
                dic_dat['y_min'] = float(line.split('=')[1])
            elif 'y_max' in line:
                dic_dat['y_max'] = float(line.split('=')[1])
            elif 'cte' in line:
                cName = line.split('=')[1]
                cValue = float(line.split('=')[2])
                dic_dat['constants'][cName] = cValue
        
        dic_dat['nFunctions'] = nFunctions

# Data parse function
def parse_data(flname, dic_dat, function_id):
    with open(flname, 'r') as inpt:
        for line in inpt:
            if line[:3] == '# [' in line:
                line = inpt.readline()    
                break
            elif ' function =>' in line:
                expr = line.split("=>")[-1]

        dat_x, dat_y = [], []
            
        while (line[:3] != '# [' and line != ''):
            dat_x.append(float(line.split()[0]))
            dat_y.append(float(line.split()[1]))
            line = inpt.readline()
            
        dic_dat['x'][function_id] = dat_x
        dic_dat['y'][function_id] = dat_y
        dic_dat['expressions'][function_id] = expr


####################################
#-------------- Main --------------#
####################################

# Set working directory to read files from
wd = os.getcwd()

# Read setup file to get extra info.
setup_data = {'x_min': np.nan, 'x_max': np.nan, 
              'y_min': np.nan, 'y_max': np.nan,
              'constants': {}, 'nFunctions': 0}
parse_setup_data(args.setup, setup_data)

# Dictionary with parsed data
dat_dic = {'x': [np.nan for i in range(setup_data['nFunctions'])], 
           'y': [np.nan for i in range(setup_data['nFunctions'])], 
           'expressions': [np.nan for i in range(setup_data['nFunctions'])]}

# Parse data
for flname in os.listdir(wd):
    if flname.endswith('.dat') and 'output_' in flname:
        function_id = int(flname.split('_')[-1][:-4])
        parse_data(flname, dat_dic, function_id)

# Run plot
plot_functions(dat_dic, setup_data)