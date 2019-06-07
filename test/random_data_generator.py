# -*- coding: utf-8 -*-
import numpy as np
from scipy.spatial import Delaunay

in_mxyz = np.random.rand(1000, 3)
in_mien = Delaunay(in_mxyz).simplices.astype(int) + 1
in_data = np.sqrt((in_mxyz**2).sum(1))

out_mxyz = np.random.rand(500, 3)

in_mxyz.byteswap().tofile('in_coordinates')
in_mien.byteswap().tofile('in_connectivity')
in_data.byteswap().tofile('in_data')
out_mxyz.byteswap().tofile('out_coordinates')



