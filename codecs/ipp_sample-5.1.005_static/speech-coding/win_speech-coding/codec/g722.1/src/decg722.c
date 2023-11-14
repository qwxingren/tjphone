/*/////////////////////////////////////////////////////////////////////////////
//
//                  INTEL CORPORATION PROPRIETARY INFORMATION
//     This software is supplied under the terms of a license agreement or
//     nondisclosure agreement with Intel Corporation and may not be copied
//     or disclosed except in accordance with the terms of that agreement.
//          Copyright(c) 2005-2006 Intel Corporation. All Rights Reserved.
//
//     Intel(R) Integrated Performance Primitives
//     USC - Unified Speech Codec interface library
//
// By downloading and installing USC codec, you hereby agree that the
// accompanying Materials are being provided to you under the terms and
// conditions of the End User License Agreement for the Intel(R) Integrated
// Performance Primitives product previously accepted by you. Please refer
// to the file ipplic.htm located in the root directory of your Intel(R) IPP
// product installation for more information.
//
// A speech coding standards promoted by ITU, ETSI, 3GPP and other
// organizations. Implementations of these standards, or the standard enabled
// platforms may require licenses from various entities, including
// Intel Corporation.
//
//
// Purpose: G.722.1 speech codec: decoder own functions.
//
*/

#include "owng722.h"

static __ALIGN32 CONST Ipp16s cnstStdDeviation_G722[REG_POW_TABLE_SIZE] = {
    0,     0,     0,      0,      0,
    0,     0,     0,      0,      0,
    0,     0,     0,      0,      0,
    0,     0,     0,      0,      0,
    0,     0,     1,      1,      1,
    1,     2,     3,      4,      6,
    8,    11,    16,     23,     32,
   45,    64,    91,    128,    181,
  256,   362,    512,   724,   1024,
 1448,  2048,   2896,  4096,   5793,
 8192, 11585,  16384, 23170,      0,
    0,     0,      0,     0,      0,
    0,     0,      0,     0
};

static __ALIGN32 CONST Ipp16s cnstDiffRegionPowerDecTree_G722[REG_NUM][DIFF_REG_POW_LEVELS-1][2] = {
{
   {  0,  0},{  0,  0},{  0,  0},{  0,  0},{  0,  0},{  0,  0},{  0,  0},{  0,  0},
   {  0,  0},{  0,  0},{  0,  0},{  0,  0},{  0,  0},{  0,  0},{  0,  0},{  0,  0},
   {  0,  0},{  0,  0},{  0,  0},{  0,  0},{  0,  0},{  0,  0},{  0,  0}
},
{
   {  1,  2},{  3,  4},{  5,  6},{  7,  8},{  9, 10},{ 11,-12},{-11,-10},{ -8, -9},
   { -7, -6},{-13, 12},{ -5, -4},{  0, 13},{ -3,-14},{ -2, 14},{ -1, 15},{-15, 16},
   {-16, 17},{-17, 18},{ 19, 20},{ 21, 22},{-18,-19},{-20,-21},{-22,-23}
},
{
   {  1,  2},{  3,  4},{  5,  6},{  7,  8},{-10, -9},{ -8,-11},{ -7, -6},{  9, -5},
   { 10,-12},{ -4, 11},{-13, -3},{ 12, -2},{ 13,-14},{ -1, 14},{ 15,-15},{  0, 16},
   {-16, 17},{-17, 18},{-18, 19},{ 20, 21},{ 22,-19},{-20,-21},{-22,-23}
},
{
   {  1,  2},{  3,  4},{  5,  6},{  7,  8},{  9, 10},{-12, 11},{-11,-13},{-10, -9},
   { 12,-14},{ -8, -7},{-15, -6},{ 13, -5},{-16, -4},{ 14,-17},{ 15, -3},{ 16,-18},
   { -2, 17},{ 18,-19},{ -1, 19},{-20, 20},{  0, 21},{ 22,-21},{-22,-23}
},
{
   {  1,  2},{  3,  4},{  5,  6},{-11,-10},{  7,-12},{  8, -9},{  9,-13},{-14, 10},
   { -8,-15},{-16, 11},{ -7, 12},{-17, -6},{ 13, 14},{-18, 15},{ -5, -4},{ 16, 17},
   { -3, -2},{-19, 18},{ -1, 19},{-20, 20},{ 21, 22},{  0,-21},{-22,-23}
},
{
   {  1,  2},{  3,  4},{  5,  6},{-12,-11},{-13,  7},{  8,-14},{-10,  9},{ 10,-15},
   { -9, 11},{ -8, 12},{-16, 13},{ -7, -6},{-17, 14},{ -5,-18},{ 15, -4},{ 16,-19},
   { 17, -3},{-20, 18},{ -2, 19},{-21, 20},{  0, 21},{ 22, -1},{-22,-23}
},
{
   {  1,  2},{  3,  4},{  5,  6},{-11,  7},{-12,-10},{-13, -9},{  8,  9},{-14, -8},
   { 10,-15},{ -7, 11},{-16, 12},{ -6,-17},{ 13, 14},{ -5, 15},{-18, 16},{ -4, 17},
   { -3,-19},{ 18, -2},{-20, 19},{ -1, 20},{  0, 21},{ 22,-21},{-22,-23}
},
{
   {  1,  2},{  3,  4},{  5,-12},{  6,-11},{-10,-13},{ -9,  7},{  8,-14},{  9, -8},
   {-15, 10},{ -7,-16},{ 11, -6},{ 12,-17},{ 13, -5},{-18, 14},{ 15, -4},{-19, 16},
   { 17, -3},{-20, 18},{ 19, 20},{ 21, 22},{  0, -2},{ -1,-21},{-22,-23}
},
{
   {  1,  2},{  3,  4},{  5,-12},{  6,-13},{-11,-10},{  7,-14},{  8, -9},{  9,-15},
   { -8, 10},{ -7,-16},{ 11, 12},{ -6,-17},{ -5, 13},{ 14, 15},{-18, -4},{-19, 16},
   { -3, 17},{ 18, -2},{-20, 19},{ 20, 21},{ 22,  0},{ -1,-21},{-22,-23}
},
{
   {  1,  2},{  3,  4},{  5,  6},{-11,-10},{-12, -9},{  7,  8},{-13, -8},{  9,-14},
   { -7, 10},{ -6,-15},{ 11, 12},{ -5,-16},{ 13, 14},{-17, 15},{ -4, 16},{ 17,-18},
   { 18, -3},{ -2, 19},{ -1,  0},{-19, 20},{-20, 21},{ 22,-21},{-22,-23}
},
{
   {  1,  2},{  3,  4},{  5,  6},{-11,  7},{-10,-12},{ -9,  8},{ -8,-13},{  9, -7},
   { 10,-14},{ -6, 11},{-15, 12},{ -5, 13},{-16, -4},{ 14, 15},{-17, -3},{-18, 16},
   { 17,-19},{ -2, 18},{-20, 19},{ -1, 20},{ 21, 22},{  0,-21},{-22,-23}
},
{
   {  1,  2},{  3,  4},{  5,-12},{  6,-11},{  7,  8},{-10,-13},{ -9,  9},{ -8,-14},
   { 10, -7},{ 11,-15},{ -6, 12},{ -5, 13},{ -4,-16},{ 14, 15},{ -3,-17},{ 16, 17},
   {-18, -2},{ 18,-19},{ -1, 19},{-20, 20},{-21, 21},{ 22,  0},{-22,-23}
},
{
   {  1,  2},{  3,  4},{  5,-12},{-13,  6},{-11,  7},{-14,  8},{-10,  9},{-15, -9},
   { -8, 10},{ -7,-16},{ 11, -6},{ 12, -5},{-17, 13},{ 14,-18},{ 15, -4},{ 16,-19},
   { 17, -3},{ 18, -2},{ 19, -1},{-20, 20},{ 21, 22},{  0,-21},{-22,-23}
},
{
   {  1,  2},{  3,  4},{-12,  5},{-11,-13},{  6,-14},{-10,  7},{  8,-15},{ -9,  9},
   {-16, 10},{ -8,-17},{ 11, 12},{ -7,-18},{ -6, 13},{ 14, -5},{ 15,-19},{ -4, 16},
   {-20, 17},{ 18, 19},{ 20, 21},{ 22,  0},{ -1, -3},{ -2,-21},{-22,-23}
}};


static __ALIGN32 CONST Ipp16s  cnstDecMLTTreeCtg0_G722[180][2] = {
{   1,   0},{   2,   3},{   4,   5},{   6,   7},
{   8,   9},{  -1, -14},{  10,  11},{  12,  13},
{  14,  15},{  16,  17},{  18,  19},{ -15,  20},
{  21,  22},{  23, -28},{  24,  -2},{  25,  26},
{  27,  28},{  29,  30},{  31,  32},{ -29,  33},
{ -16,  34},{  -3,  35},{  36,  37},{ -42,  38},
{  39,  40},{  41,  42},{  43,  44},{ -17,  45},
{ -43,  46},{  47,  48},{  -4,  49},{ -56,  50},
{  51,  52},{  53,  54},{  55,  56},{ -57,  -5},
{ -30,  57},{  58,  59},{ -18,  60},{  61, -70},
{  62,  63},{  64,  -6},{  65,  66},{ -44,  67},
{ -71,  68},{  69,  70},{ -19, -31},{ -84,  71},
{  72,  73},{  74,  75},{  76,  77},{  -7,  78},
{  79, -20},{  80,  81},{ -85,  82},{ -98,  83},
{ -58,  84},{  85, -32},{ -99,  86},{  -8,  87},
{  88,  89},{ -72, -45},{  90, -33},{  91,-112},
{ -21,  92},{ -59,-113},{ -46,  93},{  -9,  94},
{ -22,  95},{  96,  97},{  98,  99},{ -23, -86},
{ 100, 101},{ -34, -73},{ 102,-126},{-127, -35},
{ 103, -47},{ 104, 105},{ 106, 107},{-140,-100},
{-114, -87},{ 108, 109},{ 110, 111},{-141, -60},
{ 112, -48},{ 113, -24},{ -10, -61},{ 114,-101},
{ 115, 116},{ -74, -36},{ 117,-128},{ 118, -62},
{ 119, 120},{ -37, 121},{ -11, -49},{ -88, 122},
{ 123,-115},{-154, -25},{-142, 124},{-155,-129},
{ 125, -50},{ 126, 127},{ -76, -75},{ 128, 129},
{ -63, -77},{-102, -39},{ -38, 130},{ -51, 131},
{ -89,-116},{-117,-156},{ 132, -52},{ -78, 133},
{ 134,-103},{ 135, 136},{-143, -65},{ 137, -64},
{-130,-131},{ -90, 138},{-104, -91},{ -92, 139},
{-169,-183},{ -26,-118},{ 140, 141},{-144, -66},
{ -12, 142},{-168, 143},{-105,-157},{ 144,-182},
{ 145, 146},{ -79, 147},{ -53,-170},{ 148, 149},
{ -27,-145},{ 150, -80},{-106, -13},{-132, -67},
{-158, -40},{-119, 151},{ 152,-107},{ 153, 154},
{ -41,-184},{ 155, 156},{ -54, 157},{-171, 158},
{ -94, 159},{-134,-146},{ -93,-133},{-159,-108},
{ 160, -81},{ 161,-160},{ 162, -68},{-120,-122},
{-172, 163},{ -55, -95},{ 164,-109},{-161, -82},
{-173,-185},{ 165, -69},{-147,-186},{ 166, 167},
{-121, -96},{ 168,-148},{-174, 169},{ 170,-136},
{ -83, 171},{ 172, 173},{-135,-110},{-187, 174},
{-149,-150},{ 175,-123},{-162,-163},{ -97,-175},
{-188, 176},{ 177, 178},{ 179,-111},{-151,-124},
{-137,-177},{-176,-125},{-164,-138},{-189,-190}
};
static __ALIGN32 CONST Ipp16s  cnstDecMLTTreeCtg1_G722[93][2] = {
{   1,   0},{   2,   3},{   4,   5},{   6,   7},
{   8, -10},{  -1,   9},{  10,  11},{  12,  13},
{ -11,  14},{  15,  16},{  17,  18},{ -20,  -2},
{  19,  20},{ -21,  21},{  22,  23},{ -12,  24},
{  25,  26},{  27,  28},{  29,  30},{ -30,  31},
{ -31,  -3},{  32, -22},{  33, -13},{  34,  35},
{  36,  37},{  38,  39},{  40,  -4},{ -41, -14},
{  41, -40},{ -32,  42},{  43, -23},{  44,  45},
{  46,  47},{  48,  -5},{ -51, -50},{ -42,  49},
{ -33,  50},{ -15,  51},{  52,  53},{  54, -24},
{  55, -43},{  56, -52},{  57, -61},{ -60,  58},
{ -25,  59},{ -16, -34},{  -6,  60},{ -62,  61},
{ -71,  62},{ -35,  -7},{  63, -72},{ -53, -17},
{  64, -44},{ -26, -70},{  65, -45},{ -36,  66},
{ -63,  67},{ -80, -54},{ -81,  68},{ -27,  69},
{  70, -82},{ -18,  71},{  72, -55},{  73, -64},
{  74, -73},{  75, -46},{ -37,  76},{ -91,  -8},
{  -9,  77},{ -90, -83},{  78, -28},{  79, -56},
{ -65, -38},{ -74,  80},{ -19, -57},{ -92,  81},
{ -47, -48},{  82, -66},{  83, -29},{ -84,  84},
{ -75, -85},{ -67, -93},{ -39,  85},{ -76,  86},
{ -58,  87},{  88, -49},{ -94,  89},{  90, -68},
{  91, -78},{ -86, -59},{ -77, -95},{  92, -69},
{ -87, -96}
};
static __ALIGN32 CONST Ipp16s  cnstDecMLTTreeCtg2_G722[47][2] = {
{   1,   0},{   2,   3},{   4,   5},{   6,  -7},
{  -1,   7},{  -8,   8},{   9,  10},{  11,  12},
{  13, -14},{ -15,  -9},{  -2,  14},{  15,  16},
{  17,  18},{  19, -16},{  20, -22},{ -10,  21},
{ -21,  -3},{  22,  23},{  24,  25},{ -23, -17},
{  26,  27},{  28, -29},{ -11, -28},{  29,  30},
{  -4, -24},{ -30,  31},{  32, -18},{  33, -35},
{ -36,  34},{ -31, -12},{  35, -25},{  -5, -37},
{  36,  37},{ -42,  38},{ -19, -43},{ -32,  39},
{ -13, -38},{ -26, -20},{  40,  -6},{ -44,  41},
{  42, -39},{ -33, -45},{  43, -27},{  44, -46},
{  45, -34},{ -40,  46},{ -41, -47}
};
static __ALIGN32 CONST Ipp16s  cnstDecMLTTreeCtg3_G722[519][2] = {
{   1,   2},{   3,   4},{   5,   0},{   6,   7},
{   8,   9},{  10,  11},{  12,  13},{  14,  15},
{  16,  17},{-125,  18},{  -1,  19},{  20,  21},
{  22,  23},{  24,  25},{  -5, -25},{  26,  27},
{  -6,-150},{  28,  29},{  30,  31},{  32,  33},
{  34, -30},{  35,  36},{  37,  38},{  39, -31},
{-126,-155},{  40,  41},{-156,  42},{  43,-130},
{  44,-131},{-151, -26},{  45,  46},{-250,  47},
{  48,  49},{  50,  51},{  52,-275},{  53,  54},
{  -2,  -7},{  55,  56},{  57,  58},{  59,  60},
{  61,  62},{  63,  64},{  65,  66},{  67,  68},
{  69,  70},{  71, -50},{  72,-180},{  73,  74},
{  75,  76},{  77, -55},{  78,-175},{  79, -36},
{  80,  81},{ -35, -10},{  82,  83},{-280,  84},
{ -11,  85},{  86, -32},{  87,  88},{  89,-161},
{  90,-276},{  91,  92},{-281,  93},{  -8,  94},
{  95,  96},{  97,-157},{-181,-400},{-132,  98},
{-375,  99},{-160, 100},{-127, 101},{ -27, 102},
{ 103,-251},{ -56, 104},{ 105,-256},{-300,  -3},
{-152,-255},{ 106, 107},{ -37, 108},{-305, 109},
{-176, 110},{-136, 111},{ -12, 112},{ 113, 114},
{ 115,-135},{ 116, 117},{-162, 118},{ -16, -51},
{-186, 119},{ 120, 121},{ 122, 123},{ -41, 124},
{ -61, 125},{ 126, 127},{ 128, 129},{ 130, -60},
{ 131, 132},{-306, 133},{ 134,-205},{-405, 135},
{ 136, 137},{ 138, 139},{-185, 140},{ 141,-500},
{ -15, 142},{ 143, -80},{ -75, -40},{-301, 144},
{ 145, 146},{-200, 147},{ 148, 149},{ 150, 151},
{ 152,-525},{ 153,-177},{-425, 154},{ 155, -13},
{-430, 156},{ 157,-406},{ 158, 159},{-206,-380},
{ 160, 161},{ 162, 163},{ 164,-182},{-137, 165},
{-286, 166},{ 167,-401},{ 168, 169},{ -42, -33},
{ 170,-166},{ -57,-325},{ 171,-187},{ -38, 172},
{ 173, 174},{-165,-330},{  -4,-282},{ 175,-257},
{-261,-311},{-376, 176},{ 177, 178},{ -28, 179},
{ 180,  -9},{-285, 181},{ 182, 183},{ 184,-277},
{ 185,-133},{-310, -81},{ -85, 186},{-158,-210},
{ -17, 187},{ 188, 189},{ 190, -52},{-141, 191},
{ 192,-128},{-191, -20},{ 193,-140},{ 194, 195},
{-211,-260},{ 196, 197},{ 198, 199},{ 200, -66},
{-201,-225},{-381, 201},{ 202, 203},{ 204, 205},
{ 206, 207},{-163,-287},{ 208,-100},{ 209, 210},
{ 211, 212},{ 213,-252},{-105, -76},{ 214, 215},
{ 216, -21},{ -86, -62},{-307, 217},{ -65,-455},
{-550, 218},{ 219, 220},{ 221, 222},{ 223, 224},
{ 225,-230},{-142, 226},{-302,-426},{-431, 227},
{ 228, 229},{ 230,-190},{-402, -46},{-153,-450},
{-505, 231},{ 232, 233},{ 234, 235},{ 236, 237},
{ 238, 239},{-262, -29},{ 240, 241},{ 242, 243},
{-167, -67},{-331,-530},{ 244, 245},{ 246, 247},
{ 248, 249},{ 250, 251},{ 252, 253},{ 254, 255},
{ 256, 257},{ 258, 259},{ 260, 261},{ 262,-336},
{ 263,-171},{-192,-207},{-258,-138},{ 264, 265},
{ 266, 267},{ 268, 269},{ 270, 271},{ 272, 273},
{ 274, -45},{-335,-411},{ -43, -18},{-265, -71},
{-316,-326},{-350,-407},{-146, -14},{ 275, 276},
{ 277, 278},{ 279, 280},{ 281,-216},{ -34,-283},
{-291,-312},{-410,-168},{-555, 282},{ -70, -53},
{-235, -87},{ -77,-183},{-315,-332},{-178, -58},
{ 283, 284},{ 285, 286},{ 287, 288},{ 289, 290},
{ 291, 292},{ 293, 294},{ 295, 296},{ 297, 298},
{-202,-226},{-170,-267},{-134,-290},{-355,-385},
{-386, -47},{-526,-196},{ 299, 300},{ 301, 302},
{ 303, 304},{ 305, 306},{ 307, 308},{ 309, 310},
{ 311, 312},{ 313, 314},{ 315, 316},{ 317, 318},
{ 319, 320},{ 321, 322},{ 323, 324},{ 325,-111},
{-231,-253},{ -91, -82},{-172,-145},{ -22,-317},
{ -90,-356},{-382,-159},{ 326, 327},{ 328, 329},
{ 330, 331},{ 332, 333},{ 334, 335},{-106,-263},
{-278,-215},{-110, -39},{-101,-377},{-129, -63},
{-436,-195},{-506,-531},{ 336,-212},{-154,-266},
{ -59,-288},{-292,-303},{-337,-432},{-188,-451},
{-456,-460},{-501,-236},{-551, 337},{ 338, 339},
{ 340, 341},{ 342, 343},{ 344, 345},{ 346, 347},
{ 348, 349},{ 350, 351},{ 352, 353},{ 354, 355},
{ 356, 357},{ 358, 359},{ 360, 361},{ 362, 363},
{ 364, 365},{ 366, 367},{ 368, 369},{ 370, 371},
{ 372, 373},{ 374, 375},{ 376, 377},{ 378, 379},
{ 380, 381},{ 382, 383},{ 384, 385},{ 386, 387},
{ 388, 389},{ 390, 391},{ 392, 393},{ 394, 395},
{ 396, 397},{ 398, 399},{ 400, 401},{ 402, 403},
{ 404, 405},{ 406, 407},{ -72,-272},{-309,-333},
{-340,-360},{ -68,-387},{-184,-416},{-427,-147},
{-435,-437},{-115,-480},{-510,-532},{-164,-556},
{ 408,-295},{-296,-297},{-107,-313},{-193,-173},
{-320,-327},{-341,-351},{-352,-143},{-378, -19},
{-403,-412},{-268, -54},{ -83,-441},{-442,-457},
{-475, -44},{ -97,-511},{-515,-208},{-527,-528},
{-237,-536},{-552, 409},{ 410, 411},{ 412, 413},
{ 414, 415},{ 416, 417},{ 418, 419},{ 420, 421},
{ 422, 423},{ 424, 425},{ 426, 427},{ 428, 429},
{ 430, 431},{ 432, 433},{ 434, 435},{ 436, 437},
{ 438, 439},{ 440, 441},{ 442, 443},{ 444, 445},
{ 446, 447},{ 448, 449},{ 450, 451},{ 452, 453},
{ 454, 455},{ 456, 457},{ 458, 459},{ 460, 461},
{ 462, 463},{ 464, 465},{ 466, 467},{ 468, 469},
{ 470, 471},{ 472, 473},{ 474, 475},{ 476, 477},
{ 478, 479},{ 480, 481},{ 482, 483},{ 484, 485},
{ 486, 487},{ 488, 489},{ 490, 491},{ 492, 493},
{ 494, 495},{ 496, 497},{ 498, 499},{ 500, 501},
{ 502, 503},{ 504, 505},{ 506, 507},{ 508, 509},
{ 510, 511},{ 512, 513},{ 514, 515},{ 516, 517},
{ 518,-104},{ -84,-218},{-318,-319},{-117,-321},
{-322,-323},{-219,-174},{-243,-328},{-329, -94},
{-228,-194},{-240,-334},{-102,-229},{-169,-338},
{-339,-116},{-289,-342},{-343,-345},{-346,-347},
{ -23,-203},{-214,-353},{-204,-220},{-357,-358},
{-264,-361},{-362,-363},{-365,-366},{-367, -92},
{-245,-121},{-293,-379},{-108,-232},{-221,-383},
{-384,-233},{-294,-241},{-388,-389},{-390,-391},
{-392,-393},{-394,-395},{-396,-397},{-398, -24},
{-109,-149},{-242,-404},{ -64, -79},{ -89,-408},
{-409,-213},{-120,-113},{-413,-414},{-415, -96},
{-417,-418},{-419,-420},{-421,-422},{-423,-298},
{ -69,-269},{-428,-429},{ -78,-270},{ -88,-433},
{-434,-271},{-234,-259},{-438,-439},{-440,-227},
{-179,-443},{-445,-446},{-447,-223},{-238,-452},
{-453,-454},{-273,-254},{-246,-458},{-459, -48},
{-461,-462},{-463,-465},{-466,-467},{-468,-470},
{-471,-304},{-476,-477},{-478,-112},{-481,-482},
{-483,-485},{-486,-487},{-490,-491},{-103,-118},
{-502,-503},{-504,-189},{ -93,-507},{-508,-509},
{-148,-139},{-512,-513},{-308,-516},{-517,-518},
{-520,-521},{ -73, -98},{ -95, -49},{-529,-222},
{-217,-197},{-533,-534},{-535,-284},{-537,-538},
{-540,-541},{-542,-543},{-545,-546},{-144,-198},
{-314,-553},{-209,-279},{-557,-558},{-560,-561},
{-562,-563},{-565,-566},{-567,-575},{-576,-577},
{-578,-580},{-581,-582},{-583,-585},{-586,-587},
{-590,-591},{-600,-601},{-605,-606}
};
static __ALIGN32 CONST Ipp16s  cnstDecMLTTreeCtg4_G722[208][2] = {
{   1,   2},{   3,   0},{   4,   5},{   6,   7},
{   8,   9},{  10,  11},{  12, -64},{  -1,  13},
{  14, -16},{  -4,  15},{  16,  17},{  18, -80},
{  -5,  19},{  20,  21},{ -20,  22},{  23, -65},
{ -84, -21},{ -68,  24},{ -17,  25},{  26,  27},
{  28, -81},{ -69, -85},{  29,  30},{  31,  32},
{-128,  33},{  34,  35},{  -2,  36},{  37,  38},
{-144,  39},{  40,  -6},{  41,  42},{ -32,  43},
{  44,  -8},{  45, -25},{ -96,  46},{  47,-100},
{  -9,  48},{  49, -36},{  50, -24},{  51,  52},
{  53,-148},{  54,  55},{ -22,  56},{  57,  58},
{-132, -89},{  59,  60},{-101,  61},{ -37,  62},
{ -18,  63},{ -88,-129},{ -66, -70},{ -97,  64},
{ -72, -73},{  65,-145},{-149, -86},{  66, -33},
{  67,-133},{  68,  69},{  70,  71},{-192,  72},
{  73,-160},{ -82,  74},{-164,  75},{ -10,  76},
{  77,-208},{  78, -40},{  79,  80},{  -3,  81},
{  -7,  82},{  83,  84},{-104,  85},{  86, -26},
{  87,-105},{  88,-112},{  89,  90},{  91, -41},
{  92,  93},{  94,  95},{ -48,  96},{ -90,  97},
{  98, -28},{ -52,  99},{ -12, 100},{ 101, -74},
{ -13,-116},{-161, 102},{ 103, -29},{-102, 104},
{-152,-165},{ 105, 106},{ 107, 108},{ 109, 110},
{ 111,-212},{ 112, 113},{-136, 114},{ 115,-137},
{ 116, -23},{ -19,-153},{ -98,-134},{-196, 117},
{ 118, 119},{ -38,-193},{-113,-150},{-209, 120},
{ 121, -93},{ -83, 122},{ 123, 124},{ 125, 126},
{ 127, 128},{ 129, 130},{ 131, -34},{-146, -53},
{ 132, 133},{ 134, 135},{ 136, 137},{ 138,-130},
{ -49, 139},{ 140, 141},{-117, -42},{ -67, -92},
{ 142, -87},{ -77,-197},{ -71, 143},{ 144, 145},
{ 146, 147},{ 148, 149},{ 150, 151},{ 152, 153},
{ 154, 155},{ 156, 157},{ 158, 159},{ 160, 161},
{ 162, 163},{ 164, 165},{ 166, 167},{ 168, 169},
{-108, -76},{-168,-169},{-176, -44},{-224, -56},
{ -45,-180},{ -11,-106},{-213, 170},{ 171, 172},
{ 173, 174},{ 175, 176},{ 177, 178},{ 179, 180},
{ 181, 182},{ 183, 184},{ 185, 186},{ 187, 188},
{ 189, 190},{ 191, 192},{ 193, 194},{ 195, 196},
{ 197, 198},{ 199, 200},{ 201, 202},{ 203, 204},
{ 205, 206},{ 207,-131},{ -30, -27},{ -43,-151},
{ -75,-154},{-156,-162},{-109,-194},{-198,-201},
{-114,-225},{-228,-229},{-141,-142},{ -94,-124},
{ -95,-147},{-115,-125},{ -54, -55},{-107, -58},
{ -39,-155},{-121,-157},{-158,-103},{ -14,-122},
{-163, -51},{ -57,-166},{-167, -46},{-110,-170},
{-172,-173},{ -61,-177},{-178, -99},{-181,-182},
{-184,-185},{-118, -35},{ -15,-195},{ -31, -60},
{-135,-199},{-200, -79},{-202,-204},{-205,-119},
{ -91,-210},{-211, -78},{-120,-214},{-215,-216},
{-217,-218},{-220,-221},{ -50,-138},{-226,-139},
{-140,-230},{-232,-233},{-240,-241},{-244,-245}
};
static __ALIGN32 CONST Ipp16s  cnstDecMLTTreeCtg5_G722[191][2] = {
{   1,   2},{   0,   3},{   4,   5},{   6,   7},
{   8,   9},{  10,  11},{ -81,  -1},{  12,  13},
{  14, -27},{  -3,  -9},{  15,  16},{  17,  18},
{  19,  20},{-108,  21},{  -4,  22},{  23, -36},
{ -12,  24},{ -82,  25},{  26, -84},{  27, -90},
{ -10, -30},{  28,  29},{  30, -28},{  31,-117},
{ -13,  32},{ -39,  33},{  34,-109},{  35, -93},
{ -85,-111},{ -37,  36},{ -31,  37},{ -91,  38},
{  39,  40},{ -40,-120},{  41,  42},{-118,  43},
{ -94,  44},{-112,-162},{  45,  46},{  -2,  47},
{  48,  49},{-121,-189},{  50, -54},{  51,  52},
{  53, -18},{  54,  55},{  -6,  56},{  57,  -5},
{-135,  58},{  59,  60},{  61,  62},{ -63,  63},
{  64,  -7},{ -15,  65},{  66,  67},{ -45,  68},
{  69,  70},{  71, -21},{  72,  73},{  74,  75},
{  76,  77},{-163,  78},{  79,-171},{-144,  80},
{ -48,  81},{ -57,  82},{  83,  84},{-165,  85},
{ -16,-198},{  86,  87},{ -11,  88},{  89, -99},
{  90, -83},{ -19,  91},{  92,  93},{  94,  95},
{  96,  97},{  98,  99},{ -87, 100},{ 101, 102},
{-190, -66},{ -33,-192},{ 103, 104},{ 105, 106},
{-102, -42},{ 107,-126},{ 108, -29},{-129, -46},
{ -86, -14},{-114, -32},{-172, 109},{ 110, -58},
{ -34,-138},{ 111, 112},{ 113, 114},{ 115, 116},
{ 117, 118},{ 119, 120},{-127,-166},{-174, 121},
{ 122, 123},{ 124, 125},{ -88, -96},{ 126,-100},
{ -38,-110},{ -22,-136},{ -55,-139},{-201, 127},
{ -64,-193},{ 128, -49},{-175,-199},{ 129, 130},
{ 131, 132},{ 133, 134},{ 135, 136},{ 137, 138},
{ 139, 140},{ 141, 142},{ 143, 144},{ 145, 146},
{ 147, 148},{ 149, 150},{-103, -92},{ -43,-130},
{-145,-147},{-148, -41},{-216,-115},{-119,-123},
{ -95, 151},{ 152, 153},{ 154, 155},{ 156, 157},
{ 158, 159},{ 160, 161},{ 162, 163},{ 164, 165},
{ 166, 167},{ 168, 169},{ 170, 171},{ 172, 173},
{ 174, 175},{ 176, 177},{ 178, 179},{ 180, 181},
{ 182, 183},{ 184, 185},{ 186, 187},{ 188, 189},
{ 190,-153},{-180,  -8},{ -97, -24},{-122,-113},
{-124,-125},{ -67, -44},{-128, -69},{-106,-131},
{-132,-133},{ -61, -73},{-137,-116},{ -89,-140},
{-141,-142},{ -23, -25},{-146, -17},{-104,-149},
{-150,-151},{ -52,-154},{-156,-157},{ -76, -70},
{-164, -51},{ -72,-167},{-168,-169},{ -47, -20},
{-173, -59},{-101,-176},{-177,-178},{ -68,-181},
{-183,-184},{ -35, -60},{-191, -98},{ -56,-194},
{-195,-196},{ -75, -65},{-200,-105},{-202,-203},
{-204,-205},{-207,-208},{-210,-211},{ -50,-217},
{-219,-220},{-225,-226},{-228,-229}
};
static __ALIGN32 CONST Ipp16s  cnstDecMLTTreeCtg6_G722[31][2] = {
{   1,   0},{   2,   3},{   4,   5},{   6,   7},
{   8, -16},{  -1,  -8},{  -2,  -4},{   9,  10},
{  11,  12},{  13,  14},{  15,  16},{  17, -24},
{  -3, -12},{  -6,  18},{  19, -20},{ -10,  -5},
{ -17,  -9},{ -18,  20},{  21,  22},{  23,  24},
{  25, -28},{  26,  -7},{ -14, -22},{ -26, -11},
{  27, -19},{ -25, -13},{ -21,  28},{  29, -30},
{ -27,  30},{ -15, -29},{ -23, -31}
};

static __ALIGN32 CONST Ipp16s  cnstMLTQuantCentroid_G722[NUM_CATEGORIES-1][MAX_NUM_BINS] = {
{   0, 1606, 3119, 4586, 6049, 7502, 8941,
10406,11851,13292,14736,16146,17566,19351},
{   0, 2229, 4341, 6401, 8471,10531,12583,
14588,16673,18924,    0,    0,    0,    0},
{   0, 3055, 5998, 8929,11806,14680,17680,
    0,    0,    0,    0,    0,    0,    0},
{   0, 4121, 8192,12259,16322,    0,    0,
    0,    0,    0,    0,    0,    0,    0},
{   0, 5413,11071,16315,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0},
{   0, 6785,14300,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0},
{   0, 8044,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0}
};

static __ALIGN32 CONST Ipp16s  *cnstDecoderTreeTable_G722[NUM_CATEGORIES-1] = {
    (Ipp16s*)cnstDecMLTTreeCtg0_G722,
    (Ipp16s*)cnstDecMLTTreeCtg1_G722,
    (Ipp16s*)cnstDecMLTTreeCtg2_G722,
    (Ipp16s*)cnstDecMLTTreeCtg3_G722,
    (Ipp16s*)cnstDecMLTTreeCtg4_G722,
    (Ipp16s*)cnstDecMLTTreeCtg5_G722,
    (Ipp16s*)cnstDecMLTTreeCtg6_G722,
};

static __ALIGN32 CONST Ipp16s cnstNoiseFactors_G722[3] = {5793, 8192, 23170};


void DecodeFrame(SBitObj* pBitObj, Ipp16s* pRandVec, Ipp16s* pMlt,
         Ipp16s* pScale, Ipp16s* pOldScale, Ipp16s* pOldMlt, Ipp16s errFlag){
   Ipp16s absRegPowerIndices[REG_NUM];
   Ipp16s powerCategories[REG_NUM];
   Ipp16s categoryBalances[CAT_CONTROL_MAX-1];
   Ipp16u ctgCtrl;
   Ipp16s stdDeviations[REG_NUM];

   if (errFlag == 0) {
      /* convert the bits to absolute region power index and region standard deviation */
      RecoveStdDeviations(pBitObj, stdDeviations, absRegPowerIndices, pScale);
      /* fill the categorization control with CAT_CONTROL_BITS */
      ctgCtrl = (Ipp16u)GetNextBits(pBitObj, CAT_CONTROL_BITS);
      /* obtain decoder power categories and category balances */
      CategorizeFrame(pBitObj->curBitsNumber, absRegPowerIndices,
           powerCategories, categoryBalances);
      /* adjustments to the power categories and category balances */
      ArrangePowerCategories(ctgCtrl, powerCategories, categoryBalances);
      /* decode mlt */
      DecodeBitsToMlt(pBitObj, pRandVec, stdDeviations, powerCategories, pMlt);
      /* test for frame errors */
      TestFrame(pBitObj, errFlag, ctgCtrl, absRegPowerIndices);
   }
   /* perform error handling  */
   ProcessErrors(&errFlag, pMlt, pOldMlt, pScale, pOldScale);
}

/*F*
//  Name:      RecoveStdDeviations
//  Purpose:   Recove stdDeviations and absRegPowerIndices from code bits
*F*/
void RecoveStdDeviations(SBitObj* pBitObj, Ipp16s *pStdDeviations,
         Ipp16s *pRegPowerIndices, Ipp16s *pScale) {
   Ipp16s regNum, i;
   Ipp16s index;
   Ipp16s diffIndex[REG_NUM];
   Ipp16s maxIndex;
   Ipp16s temp;

   index = (Ipp16s)GetNextBits(pBitObj, 5);
   diffIndex[0] = (short)(index - ESF_ADJUSTMENT_TO_RMS_INDEX);
   for (regNum=1; regNum<REG_NUM; regNum++) {
      index = 0;
      do {
         index = cnstDiffRegionPowerDecTree_G722[regNum][index][GetNextBits(pBitObj, 1)];
      } while (index > 0);
      diffIndex[regNum] = (short)(-index);
   }
   /* Reconstruct absRegPowerIndices[] from diffIndex[]. */
   pRegPowerIndices[0] = diffIndex[0];
   for (regNum=1; regNum<REG_NUM; regNum++)
      pRegPowerIndices[regNum] =
         (short)(pRegPowerIndices[regNum-1] + diffIndex[regNum] + DRP_DIFF_MIN);
   /* Reconstruct stdDeviations[] from absRegPowerIndices[]. */
   temp = 0;
   maxIndex = 0;
   for (regNum=0; regNum<REG_NUM; regNum++) {
      i = (short)(pRegPowerIndices[regNum] + REG_POW_TABLE_NUM_NEGATIVES);
      if (i > maxIndex)
         maxIndex = i;
      temp = (short)(temp + cnstStdDeviation_G722[i]);
   }
   i = 9;
   while ((i >= 0) && ((temp >= 8) || (maxIndex > 28))) {
      i--;
      temp>>=1;
      maxIndex -= 2;
   }
   *pScale = i;
   temp = (Ipp16s )(REG_POW_TABLE_NUM_NEGATIVES + 2 * i);
   for (regNum=0; regNum<REG_NUM; regNum++) {
      i = (short)(pRegPowerIndices[regNum] + temp);
      pStdDeviations[regNum] = cnstStdDeviation_G722[i];
   }
}

/*F*
//  Name:      ArrangePowerCategories
//  Purpose:   Arrange the power categories based on the categorization control
*F*/
void ArrangePowerCategories(Ipp16s ctgCtrl, Ipp16s* pPowerCtgs, Ipp16s* pCtgBalances){
   Ipp16s regNum, i=0;

   while (ctgCtrl > 0) {
      regNum = pCtgBalances[i++];
      pPowerCtgs[regNum]++;
      ctgCtrl--;
   }
}

/*F*
//  Name:      DecodeBitsToMlt
//  Purpose:   decode the quantized bits into mlt coefs
*F*/
void DecodeBitsToMlt(SBitObj* pBitObj, Ipp16s* pRandVec,
         Ipp16s* pStdDeviations, Ipp16s* pPowerCtgs, Ipp16s* pMlt) {
   Ipp16s stdDeviation;
   Ipp16s *pCurMlt;
   Ipp16s mltValue;
   Ipp16s noifillpos;
   Ipp16s noifillneg;
   Ipp16s regNum, ctgNum, j, n;
   Ipp16s k[MAX_VECTOR_DIMENSION];
   Ipp16s vecDim, nVecs;
   Ipp16s index;
   Ipp16s signsIndex=0;
   Ipp16s bit=0;
   Ipp16s nSignBits;
   Ipp16s outFlag;
   Ipp16s *pDecoderTable;
   Ipp16s randWord;

   outFlag = 0;
   for (regNum=0; regNum<REG_NUM; regNum++) {
      ctgNum = pPowerCtgs[regNum];
      pCurMlt = &pMlt[regNum*REG_SIZE];
      stdDeviation = pStdDeviations[regNum];
      if (ctgNum < 7) {
         pDecoderTable = (Ipp16s *) cnstDecoderTreeTable_G722[ctgNum];
         vecDim = cnstVectorDimentions_G722[ctgNum];
         nVecs = cnstNumberOfVectors_G722[ctgNum];
         for (n=0; n<nVecs; n++) {
            index = 0;
            do {
               if (pBitObj->curBitsNumber <= 0) {
                  outFlag = 1;
                  break;
               }
                index = (Ipp16s)*(pDecoderTable + 2 * index + GetNextBits(pBitObj, 1));
            } while (index > 0);
            if (outFlag != 0)
               break;
            index = (short)(-index);
            /* get the number of sign bits */
            nSignBits = ExpandIndexToVector(index, k, ctgNum);
            if (pBitObj->curBitsNumber >= nSignBits) {
               if (nSignBits != 0) {
                  signsIndex = (Ipp16s)GetNextBits(pBitObj, nSignBits);
                  bit = (short)(1 << (nSignBits-1));
               }
                for (j=0; j<vecDim; j++) {
                  mltValue = (short)((stdDeviation * cnstMLTQuantCentroid_G722[ctgNum][k[j]]) >> 12);
                  if (mltValue != 0) {
                     if ((signsIndex & bit) == 0)
                        mltValue = (short)(-mltValue);
                     bit >>= 1;
                  }
                  *pCurMlt++ = mltValue;
               }
            } else {
               outFlag = 1;
               break;
            }
         }

         if (outFlag != 0) {
            /* noise fill */
            for (j=(short)(regNum+1); j<REG_NUM; j++)
               pPowerCtgs[j] = 7;
            ctgNum = 7;
            pCurMlt = &pMlt[regNum*REG_SIZE];
         }
      }
      if ((ctgNum == 5) || (ctgNum == 6)){
         pCurMlt = &pMlt[regNum*REG_SIZE];
         noifillpos = (short)((stdDeviation * cnstNoiseFactors_G722[ctgNum - 5])>>15);
         noifillneg = (short)(-noifillpos);
         randWord = GetRand(pRandVec);
         for (j=0; j<10; j++) {
            if (*pCurMlt == 0) {
               if ((randWord & 1) == 0)
                  *pCurMlt = noifillneg;
               else
                  *pCurMlt = noifillpos;
               randWord >>= 1;
            }
            pCurMlt++;
         }
         randWord = GetRand(pRandVec);
         for (j=0; j<10; j++) {
            if (*pCurMlt == 0) {
               if ((randWord & 1) == 0)
                  *pCurMlt = noifillneg;
               else
                  *pCurMlt = noifillpos;
               randWord  >>= 1;
            }
            pCurMlt++;
         }
      } else if (ctgNum == 7) {
         index = (short)(ctgNum - 5);
         noifillpos = (short)((stdDeviation * cnstNoiseFactors_G722[index])>>15);
         noifillneg = (short)(-noifillpos);
         randWord = GetRand(pRandVec);
         for (j=0; j<10; j++) {
            if ((randWord & 1) == 0)
               *pCurMlt++  = noifillneg;
            else
               *pCurMlt++  = noifillpos;
            randWord >>= 1;
         }
         randWord = GetRand(pRandVec);
         for (j=0; j<10; j++) {
            if ((randWord & 1) == 0)
               *pCurMlt++ = noifillneg;
            else
               *pCurMlt++ = noifillpos;
            randWord >>= 1;
         }
      }
   }
   if (outFlag)
      pBitObj->curBitsNumber--;
}

/*F*
//  Name:      ExpandIndexToVector
//  Purpose:   Computes a vector of sign bits with the length of the category vector
//             Returns the number of sign bits in the vector
*F*/
Ipp16s ExpandIndexToVector(Ipp16s index, Ipp16s* pVector, Ipp16s ctgNumber){
   Ipp16s i, q, p;
   Ipp16s maxBin, maxBinInv;
   Ipp16s nSignBits = 0;

   maxBin = (short)(cnstMaxBin_G722[ctgNumber] + 1);
   maxBinInv = cnstMaxBinInverse_G722[ctgNumber];
   p = index;
   for (i=(short)(cnstVectorDimentions_G722[ctgNumber]-1); i>=0; i--){
      q = (short)((p * maxBinInv)>>15);
      pVector[i] = (short)(p - q * maxBin);
      p = q;
      if (pVector[i] != 0)
         nSignBits++;
   }
   return nSignBits;
}

/*F*
//  Name:      TestFrame
//  Purpose:   Tests frame for error conditions and sets the errFlag accordingly
*F*/
void TestFrame(SBitObj* pBitObj, Ipp16s errFlag,
                         Ipp16s ctgCtrl, Ipp16s *pRegPowerIndices){
   Ipp16s i;

   if (pBitObj->curBitsNumber > 0){
      for (i=0; i<pBitObj->curBitsNumber; i++){
         GetNextBit(pBitObj);
         if (pBitObj->nextBit == 0)
            errFlag = 1;
      }
   } else {
      if ((ctgCtrl < CAT_CONTROL_NUM-1) &&
         (pBitObj->curBitsNumber < 0))
         errFlag |= 2;
   }
   /* checks stdDeviations  */

   for (i=0; i<REG_NUM; i++){
      if ((pRegPowerIndices[i] > 31 - ESF_ADJUSTMENT_TO_RMS_INDEX) ||
         (pRegPowerIndices[i] < -8 - ESF_ADJUSTMENT_TO_RMS_INDEX))
         errFlag |= 4; /* error flag  */
   }
}

/*F*
//  Name:      ProcessErrors
//  Purpose:   For error in current frame repeat the previous mlt.
//             Otherwise, set the mlt coefficients to 0.
*F*/
void ProcessErrors(Ipp16s* pErrFlag, Ipp16s* pMlt, Ipp16s* pOldMlt,
                    Ipp16s* pScale, Ipp16s* pOldScale){
   if (*pErrFlag != 0) {
      ippsCopy_16s(pOldMlt, pMlt, NUMBER_OF_VALID_COEFS);
      ippsZero_16s(pOldMlt, NUMBER_OF_VALID_COEFS);
      *pScale = *pOldScale;
      *pOldScale = 0;
   } else {
      ippsCopy_16s(pMlt, pOldMlt, NUMBER_OF_VALID_COEFS);
      *pOldScale = *pScale;
   }
   ippsZero_16s(&pMlt[NUMBER_OF_VALID_COEFS], DCT_LENGTH-NUMBER_OF_VALID_COEFS);
}
