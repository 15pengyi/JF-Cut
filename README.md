JF-Cut
==========

Graph Cut has proven to be an effective scheme to solve a wide variety of segmentation problems in vision and graphics community.
The main limitation of conventional graph-cut implementations is that they can hardly handle large images or videos because of high computational complexity.
Even though there are some parallelization solutions, they commonly suffer from the problems of low parallelism (on CPU) or low convergence speed (on GPU).

In this paper, we present a novel graph cut algorithm that leverages a parallelized jump flooding (JF) technique and a heuristic push-relabel scheme to enhance the graph cut process, namely, back-and-forth relabel, convergence detection and block-wise push-relabel.
The entire process is parallelizable on GPU, and outperforms existing GPU-based implementations in terms of global convergence, information propagation, and performance.
We design an intuitive user interface for specifying interested regions in cases of occlusions when handling video sequences.
Experiments on a variety of data sets, including images (up to $15K × 10K$), videos (up to $2.5K × 1.5K × 50$), and volumetric data, achieve high quality results and a maximum 40-fold (139-fold) speedup over conventional GPU- (CPU-) based approaches.

Image Segmentation
-------
See [details](https://github.com/15pengyi/JF-Cut/wiki/I-Image-Segmentation).

Video Cutout
-------
See [details](https://github.com/15pengyi/JF-Cut/wiki/II-Video-Cutout).

Volume Segmentation
-------
See [details](https://github.com/15pengyi/JF-Cut/wiki/III-Volume-Segmentation).

Performance
-------
See [details](https://github.com/15pengyi/JF-Cut/wiki/IV-Performance).

IEEE Transactions on Image Processing
-------
See [details](http://dx.doi.org/10.1109/TIP.2014.2378060)
