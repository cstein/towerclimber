import matplotlib.pyplot as plt
from matplotlib.path import Path
import matplotlib.patches as patches

from dungeon import Dungeon

###############################################################
###############################################################
###############################################################
def dungeon2patch( dungeon, color, lw=0.0 ):
    verts = [ (dungeon._x1, dungeon._y1),
              (dungeon._x1, dungeon._y2),
              (dungeon._x2, dungeon._y2),
              (dungeon._x2, dungeon._y1),
              ( 0.0, 0.0)
              ]

    codes = [Path.MOVETO,
         Path.LINETO,
         Path.LINETO,
         Path.LINETO,
         Path.CLOSEPOLY,
         ]

    path = Path( verts, codes )

    return patches.PathPatch( path, facecolor=color, linewidth=0.0, alpha=1.0)
###############################################################
###############################################################
###############################################################
def dopatches( dungeon, color ):

    ax.add_patch( dungeon2patch( dungeon, color ))
    #print tree.leaf

    if not dungeon.IsLeaf():
        dopatches(dungeon.l, 'white')
        dopatches(dungeon.r, 'white')

        d = Dungeon( dungeon.l._cx -2, dungeon.l._cy -2, dungeon.r._cx +2, dungeon.r._cy +2)
        ax.add_patch( dungeon2patch( d, 'gray' ))
    else:
        if dungeon.room is not None:
            ax.add_patch( dungeon2patch( dungeon.room, 'gray' ))
###############################################################
###############################################################
###############################################################

if __name__ == '__main__':
    x2 = 512.0
    y2 = 512.0
    r = Dungeon( 0.0, 0.0, x2, y2 )
    r.Split(8)
    print r

    w = 10.0
    h = w * r._height / r._width
    fig = plt.figure(figsize=(w,h))
    ax = fig.add_subplot(111)
    
    #ax.add_patch( dungeon2patch( r ) )
    dopatches( r, 'white' )
    
    ax.set_xlim( r._x1 - 10, r._x2 + 10 )
    ax.set_ylim( r._y1 - 10, r._y2 + 10 )
    plt.show()
