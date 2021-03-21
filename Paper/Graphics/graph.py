#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt

nodes = ['corner nodes', 'edge nodes', 'inner nodes']
plt.plot(nodes, [867, 1095, 1586], label='global = 1000, local = 256, blocking')
plt.plot(nodes, [929, 1176, 1703], label='global = 500, local = 512')
plt.plot(nodes, [732, 848, 1172], label='global = 1000, local = 256')
plt.plot(nodes, [651, 709, 942], label='global = 2000, local = 128')
plt.plot(nodes, [608, 652, 843], label='global = 4000, local = 64')
plt.legend()
plt.ylabel('elapsed seconds (median)')

plt.show()

plt.clf()

plt.plot(nodes, [754, 527, 35], label='global = 1000, local = 256, blocking')
plt.plot(nodes, [852, 606, 80], label='global = 500, local = 512')
plt.plot(nodes, [591, 475, 153], label='global = 1000, local = 256')
plt.plot(nodes, [625, 567, 334], label='global = 2000, local = 128')
plt.plot(nodes, [649, 606, 415], label='global = 4000, local = 64')
plt.legend()
plt.ylabel('elapsed seconds (median)')

plt.show()