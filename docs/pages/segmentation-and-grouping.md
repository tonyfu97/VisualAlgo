# 3. Segmentation and Grouping

## Computer Vision Algorithms
### Region Growing
### Watershed
### K-means Clustering
### Mean Shift
### GrabCut
### U-Net
### Region Proposal Network (RPN)

---

## Neuroscience Models

### The FBF Model

**Reference**: Grossberg and Wyse, "Figure-Ground Separation of Connected Scenic Figures: Boundaries, Filling-In, and Opponent Processing", *Neural Networks For Vision and Image Processing*, Chapter 7, 1992. [(Link to paper with the same topic but low scan quality)](https://sites.bu.edu/steveg/files/2016/06/GroWyse1991NN.pdf)

**Overview**: 

The FBF network model was used as part of the larger pattern recognition model by Grossberg et al.. It handles the initial steps of processing, up until the figure-ground separation phase. 

The FBF model is composed of two sub-systems: the Feature Contour System (FCS) and the Boundary Contour System (BCS), both initially proposed by Grossberg and Mingolla in 1985. As the processing sequence typically follows the pattern FCS-BCS-FCS, these combined systems are collectively referred to as the FBF networks.

The central idea posited by Grossberg is that these two systems collaboratively enable us to recognize surfaces (handled by the FCS) and boundaries (handled by the BCS). The FCS's role is to fill in the entire boundary region with consistent surface characteristics, relying heavily on the boundaries computed by the BCS, which connects collinear contours to establish these boundaries. A notable point raised by Grossberg is our ability to recognize boundaries even when they're not directly visible, leading to illusions such as the Kanizsa triangle.

It's important to note that the FCS and BCS are hypothetical models for the visual system, distinguished by their function ("what" they are supposed to do) rather than their mechanism ("how" they are supposed to operate). These models have evolved significantly over time, and their implementation is not bound by any specific method or model. The exact details often depend on specific research papers. Also, note that I've made a number of simplifications to the original model. The original paper applied mathematics based on sub-pixel resolution (interpolating pixels), whereas the simple cells I used are entirely pixel-based.

**Algorithm Breakdown**: 

The FBF model algorithm consists of four steps. The first is as follows:

* **Step 1: Discount the Illuminant**: Instead of uniformly applying the ON-Center-OFF-Surround (ON-C) and OFF-Center-ON-Surround (OFF-C) kernels (also known as Difference of Gaussian), the kernel is scaled with the image value to handle areas with varying brightness levels. Grossberg describes these cells as "shunting" because their dynamics are dependent on their current state, akin to an electrical system with a (shunting) resistor. This is believed to be part of the FCS's work, as it needs to perceive surfaces as continuous over a broad range of illumination levels. The output of the ON-C and OFF-C processes are denoted as \(\mathbf{x}\) and \(\bar{\mathbf{x}}\) respectively:

    $$ \mathbf{x} = \frac{\mathbf{I} \otimes (B \mathbf{C} - D \mathbf{E})}{A + \mathbf{I} \otimes (\mathbf{C} + \mathbf{E})}\\
    \bar{\mathbf{x}} = \frac{A * S + \mathbf{I} \otimes (D \mathbf{E} - B \mathbf{C})}{A + \mathbf{I} \otimes (\mathbf{C} + \mathbf{E})}$$

    Here, the symbol \(\otimes\) represents the operation of 2D cross-correlation. \(\mathbf{I}\) represents the input image array, while \(A\), \(B\), and \(D\) are constants that define the shape of the ON-C and OFF-C kernels. The term \(S\) introduces the offset of the OFF-C kernel, ensuring that \(\bar{\mathbf{x}}\) primarily falls within the positive range. The values for those parameters can also be found in the paper.

    \(\mathbf{C}\) and \(\mathbf{E}\) denote two Gaussian kernels, as the ON-C and OFF-C kernels are Differences of Gaussians. The ON-C shape is derived from subtracting the wider and shorter Gaussian kernel \(\mathbf{E}\) from the narrower and taller Gaussian kernel \(\mathbf{C}\). For the OFF-C kernel, the procedure is reversed. The formulas for these kernels are:

    $$
    \mathbf{C} = C e^{-\frac{(p - i)^2 + (q - j)^2)}{\alpha^2}}\\
    \mathbf{E} = E e^{-\frac{(p - i)^2 + (q - j)^2)}{\beta^2}}\\
    $$

    where \(\alpha\) and \(\beta\) are two other constants. (Interestingly, Grossberg and Wyse applied a logarithmic transformation to the arguments of the exponent in their paper, a step that I did not use in my implementation. Instead, I use the "standard" form of Gaussian shown above.)

* **Step 2: CORT-X 2 Filter**: CORT-X 2 Filter is neurophysiologically inspired model based on Hubel and Wisels work on Simple, Complex, and Hypercomplex cells. They are the BCS part of this model. The CORT-X 2 Filter receives input from the previous step and outputs the boundaries. It can be further broken down into 


### CONFIGR (Carpenter, Gaddam, and Mingolla, 2007)
* [Paper](https://pubmed.ncbi.nlm.nih.gov/18024082/)


### Tolerance Space Theory (TST) for Gestalt Proximity Principle (Peng, Yang, and Li, 2021)
* [Paper](https://jov.arvojournals.org/article.aspx?articleid=2772625)


### Gestalt Laws Models
### Border Ownership Models
