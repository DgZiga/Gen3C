
//{{BLOCK(built_graphics)

//======================================================================
//
//	built_graphics, 256x160@4, 
//	+ palette 20 entries, lz77 compressed
//	+ 121 tiles (t|f|p reduced) lz77 compressed
//	+ regular map (flat), lz77 compressed, 32x20 
//	Total size: 40 + 1236 + 424 = 1700
//
//	Time-stamp: 2023-12-09, 16:24:55
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BUILT_GRAPHICS_H
#define GRIT_BUILT_GRAPHICS_H

#define built_graphicsTilesLen 1236
extern const unsigned char built_graphicsTiles[1236];

#define built_graphicsMapLen 424
extern const unsigned short built_graphicsMap[212];

#define built_graphicsPalLen 40
extern const unsigned char built_graphicsPal[40];

#endif // GRIT_BUILT_GRAPHICS_H

//}}BLOCK(built_graphics)
