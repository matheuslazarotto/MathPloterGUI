# Variables and auxiliary functions for further 
# use in general programs.
#
# Made by: M. J. Lazarotto (20/08/2020)

import numpy as np
from fractions import Fraction as frac

# Color_list (based on matplotlib color chart)
colors_1 = ['black', 'dimgray', 'gray', 'darkgray', 'silver', 
            'lightcoral', 'brown', 'firebrick', 'darkred', 
            'red', 'coral', 'lightsalmon', 'sienna', 'saddlebrown', 
            'sandybrown', 'darkorange', 'tan', 'goldenrod', 
            'gold', 'olive', 'darkolivegreen', 'lawngreen', 
            'darkseagreen', 'forestgreen', 'turquoise', 
            'darkslategray', 'darkcyan', 'steelblue', 
            'dodgerblue', 'midnightblue', 'darkviolet',
            'purple', 'orchid']

colors_2 = ['firebrick', 'orangered', 'goldenrod', 'gold', 
            'olive', 'darkolivegreen', 
            'green', 'turquoise', 'teal', 'skyblue', 'dodgerblue', 
            'midnightblue', 'blueviolet', 'purple', 'magenta']

colors_3 = ['black', 'gray', 'sienna', 'firebrick', 'orangered', 
            'orange', 'goldenrod', 'gold', 'olive', 'darkolivegreen', 
            'green', 'turquoise', 'teal', 'skyblue', 'dodgerblue', 
            'midnightblue', 'blueviolet', 'purple', 'magenta']

colors_std_matplotlib = ['#1f77b4', '#ff7f0e', '#2ca02c', '#d62728', '#bcbd22', 
                         '#e377c2', '#7f7f7f', '#9467bd', '#8c564b', '#17becf']
                         
# Converts a float into a string of PI fraction
# LaTeX format: \frac{num}{den}\pi
def lbl_pi(val, pos):
    N = np.round(val/np.pi, 3)
    num = int(frac(N).limit_denominator(50).numerator)
    den = int(frac(N).limit_denominator(50).denominator)

    if (num == 0):
        return r'$0$'
    elif (num == den):
        return r'$\pi$'
    elif (num == -den):
        return r'$-\pi$'
    elif (den == 1):
        return r'$%d\pi$' % num
    elif (num == 1):
        return r'$\frac{\pi}{%d}$' % den
    elif (num == -1):
        return r'$-\frac{\pi}{%d}$' % den
    else:
        return r'$\frac{%d}{%d}\pi$' % (num, den)

# skip [N] lines from [inpt] file
def skipline(inpt, N):
    for i in range(N):
       line = inpt.readline()
    return line