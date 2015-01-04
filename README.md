JF-Cut
==========

In JF-Cut, we present a novel graph cut algorithm that leverages a parallelized jump flooding (JF) technique and a heuristic pushing and relabeling scheme to enhance the components of the graph cut process, namely, multi-pass relabel, convergence detection and block-wise push-relabel. The entire process is parallelizable on GPU, and outperforms existing GPU-based implementations in terms of global convergence, information propagation, and performance. We design an intuitive user interface for specifying interested regions
in cases of occlusions when handling volumetric data or video sequences. Experiments on a variety of datasets, including images (up to 15K × 10K), videos (up to 2.5K × 1.5K × 50), and volumetric data, achieve high quality results and a maximum 164-fold speedup over conventional approaches.


Image Segmentation
-------
See [details](https://github.com/15pengyi/JF-Cut/wiki/I-Image-Segmentation).

Video Cutout
-------
See [details](https://github.com/15pengyi/JF-Cut/wiki/II-Video-Cutout).

Volume Segmentation
-------
See [details](https://github.com/15pengyi/JF-Cut/wiki/III-Volume-Segmentation).

Experiment Result
-------
See [details](https://github.com/15pengyi/JF-Cut/wiki/IV-Experiment-Result).
