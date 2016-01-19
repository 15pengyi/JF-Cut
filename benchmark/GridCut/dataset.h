#ifndef DATASET_H_
#define DATASET_H_

struct Instance
{
  const char* name;
  int         count;
  const char* filename;
};

const Instance instances[] = {
  /**
  { "/ctu/lazybrush/footman",                    8, "%s/ctu/lazybrush/footman/footman%d.mfi" },
  { "/ctu/lazybrush/hmdman",                     6, "%s/ctu/lazybrush/hmdman/hmdman%d.mfi" },
  { "/ctu/lazybrush/mangadinner",               10, "%s/ctu/lazybrush/mangadinner/mangadinner%d.mfi" },
  { "/ctu/lazybrush/mangagirl",                  7, "%s/ctu/lazybrush/mangagirl/mangagirl%d.mfi" },
  { "/ctu/lazybrush/elephant",                   3, "%s/ctu/lazybrush/elephant/elephant%d.mfi" },
  { "/ctu/lazybrush/bird",                       3, "%s/ctu/lazybrush/bird/bird%d.mfi" },
  { "/ctu/lazybrush/doctor",                     5, "%s/ctu/lazybrush/doctor/doctor%d.mfi" },

  { "/middlebury/denoise/penguin",             256, "%s/middlebury/denoise/penguin/penguin%d.mfi" },
  { "/middlebury/denoise/house",               256, "%s/middlebury/denoise/house/house%d.mfi" },

  { "/middlebury/stereo/tsukuba",               15, "%s/middlebury/stereo/tsukuba/tsukuba%d.mfi" },
  { "/middlebury/stereo/venus",                 19, "%s/middlebury/stereo/venus/venus%d.mfi" },
  { "/middlebury/stereo/teddy",                 59, "%s/middlebury/stereo/teddy/teddy%d.mfi" },
  { "/middlebury/segmentation/flower",           3, "%s/middlebury/segmentation/flower/flower%d.mfi" },
  { "/middlebury/segmentation/person",           3, "%s/middlebury/segmentation/person/person%d.mfi" },
  { "/middlebury/segmentation/sponge",           3, "%s/middlebury/segmentation/sponge/sponge%d.mfi" },
  { "/middlebury/photomontage/family",          20, "%s/middlebury/photomontage/family/family%d.mfi" },
  { "/middlebury/photomontage/panorama",        21, "%s/middlebury/photomontage/panorama/panorama%d.mfi" },

  { "/uwo/stereo/BVZ-tsukuba",                  16, "%s/uwo/stereo/BVZ-tsukuba/BVZ-tsukuba%d.mfi" },
  { "/uwo/stereo/BVZ-sawtooth",                 20, "%s/uwo/stereo/BVZ-sawtooth/BVZ-sawtooth%d.mfi" },
  { "/uwo/stereo/BVZ-venus",                    22, "%s/uwo/stereo/BVZ-venus/BVZ-venus%d.mfi" },

  { "/uwo/shapefit/LB07-bunny-sml",              1, "%s/uwo/shapefit/LB07-bunny-sml.mfi" },
  { "/uwo/shapefit/LB07-bunny-med",              1, "%s/uwo/shapefit/LB07-bunny-med.mfi" },
  
  { "/uwo/segment/bone_subxyz_subxy.n6c10",      1, "%s/uwo/segmentation/bone/bone_subxyz_subxy.n6c10.mfi" },
  { "/uwo/segment/bone_subxyz_subx.n6c10",       1, "%s/uwo/segmentation/bone/bone_subxyz_subx.n6c10.mfi" },
  { "/uwo/segment/bone_subxyz.n6c10",            1, "%s/uwo/segmentation/bone/bone_subxyz.n6c10.mfi" },
  { "/uwo/segment/bone_subxy.n6c10",             1, "%s/uwo/segmentation/bone/bone_subxy.n6c10.mfi" },
  { "/uwo/segment/bone_subx.n6c10",              1, "%s/uwo/segmentation/bone/bone_subx.n6c10.mfi" },
  
  { "/uwo/segment/bone.n6c10",                   1, "%s/uwo/segmentation/bone/bone.n6c10.mfi" },
  { "/uwo/segment/liver.n6c10",                  1, "%s/uwo/segmentation/liver/liver.n6c10.mfi" },
  { "/uwo/segment/babyface.n6c10",               1, "%s/uwo/segmentation/babyface/babyface.n6c10.mfi" },
  { "/uwo/segment/adhead.n6c10",                 1, "%s/uwo/segmentation/adhead/adhead.n6c10.mfi" },
  
  { "/uwo/segment/bone_subxyz_subxy.n6c100",     1, "%s/uwo/segmentation/bone/bone_subxyz_subx.n6c100.mfi" },
  { "/uwo/segment/bone_subxyz_subx.n6c100",      1, "%s/uwo/segmentation/bone/bone_subxyz_subx.n6c100.mfi" },
  { "/uwo/segment/bone_subxyz.n6c100",           1, "%s/uwo/segmentation/bone/bone_subxyz.n6c100.mfi" },
  { "/uwo/segment/bone_subxy.n6c100",            1, "%s/uwo/segmentation/bone/bone_subxy.n6c100.mfi" },
  { "/uwo/segment/bone_subx.n6c100",             1, "%s/uwo/segmentation/bone/bone_subx.n6c100.mfi" },

  { "/uwo/segment/bone.n6c100",                  1, "%s/uwo/segmentation/bone/bone.n6c100.mfi" },
  { "/uwo/segment/liver.n6c100",                 1, "%s/uwo/segmentation/liver/liver.n6c100.mfi" },
  { "/uwo/segment/babyface.n6c100",              1, "%s/uwo/segmentation/babyface/babyface.n6c100.mfi" },
  { "/uwo/segment/adhead.n6c100",                1, "%s/uwo/segmentation/adhead/adhead.n6c100.mfi" },

  { "/uwo/segment/bone_subxyz_subxy.n26c10",     1, "%s/uwo/segmentation/bone/bone_subxyz_subxy.n26c10.mfi" },
  { "/uwo/segment/bone_subxyz_subx.n26c10",      1, "%s/uwo/segmentation/bone/bone_subxyz_subx.n26c10.mfi" },
  { "/uwo/segment/bone_subxyz.n26c10",           1, "%s/uwo/segmentation/bone/bone_subxyz.n26c10.mfi" },
  { "/uwo/segment/bone_subxy.n26c10",            1, "%s/uwo/segmentation/bone/bone_subxy.n26c10.mfi" },
  { "/uwo/segment/bone_subxyz_subxy.n26c100",    1, "%s/uwo/segmentation/bone/bone_subxyz_subxy.n26c100.mfi" },
  { "/uwo/segment/bone_subxyz_subx.n26c100",     1, "%s/uwo/segmentation/bone/bone_subxyz_subx.n26c100.mfi" },
  { "/uwo/segment/bone_subxyz.n26c100",          1, "%s/uwo/segmentation/bone/bone_subxyz.n26c100.mfi" },
  { "/uwo/segment/bone_subxy.n26c100",           1, "%s/uwo/segmentation/bone/bone_subxy.n26c100.mfi" },
  /*/
  { "middlebury-flower",                       1, "%s/jackie/flower.mfi" },
  { "middlebury-person",                       1, "%s/jackie/person.mfi" },
  { "middlebury-sponge",                       1, "%s/jackie/sponge.mfi" },
  { "uwo-bone",                                1, "%s/jackie/bone.mfi" },
  { "uwo-liver",                               1, "%s/jackie/liver.mfi" },
  { "uwo-babyface",                            1, "%s/jackie/babyface.mfi" },
  { "uwo-adhead",                              1, "%s/jackie/adhead.mfi" },
  { "image-madagascar",                        1, "%s/jackie/madagascar.mfi" },
  { "image-lta",                               1, "%s/jackie/lta.mfi" },
  { "video-4k",                                1, "%s/jackie/4k.mfi" },
  { "video-croods",                            1, "%s/jackie/croods.mfi" },
  { "video-pi",                                1, "%s/jackie/pi.mfi" },
  { "volume-brain",                            1, "%s/jackie/brain.mfi" },
  { "volume-lobster",                          1, "%s/jackie/lobster.mfi" },
  //*/
};

#endif
