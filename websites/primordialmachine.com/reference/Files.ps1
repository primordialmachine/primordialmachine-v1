# Copyright (c) 2022 Michael Heilmann. All rights reserved.
$jobs +=
  @(
    # Reference.
    @('./reference/index.html.template',
      './reference/index.html'),

    # Reference - Projection & Picking
    @('./reference/projection.html.template',
      './reference/projection.html'),
    @('./reference/picking.html.template',
      './reference/picking.html'),

    # Reference - Definitions.
    @('./reference/definitions.html.template',
      './reference/definitions.html'),
    @('./reference/definitions/axis-aligned-box.html.template',
      './reference/definitions/axis-aligned-box.html'),
    @('./reference/definitions/ray.html.template',
      './reference/definitions/ray.html'),
    @('./reference/definitions/sphere.html.template',
      './reference/definitions/sphere.html'),
    @('./reference/definitions/line.html.template',
      './reference/definitions/line.html'),
    @('./reference/definitions/line-segment.html.template',
      './reference/definitions/line-segment.html'),
    @('./reference/definitions/cross-product.html.template',
      './reference/definitions/cross-product.html'),
    @('./reference/definitions/cross-product-matrix.html.template',
      './reference/definitions/cross-product-matrix.html'),
    @('./reference/definitions/second-power-of-the-cross-product-matrix.html.template',               
      './reference/definitions/second-power-of-the-cross-product-matrix.html'),
    @('./reference/definitions/vector-projection-and-rejection.html.template',                       
      './reference/definitions/vector-projection-and-rejection.html'),

    # Reference - Transformations.
    @('./reference/transformations.html.template',
      './reference/transformations.html'),
    @('./reference/transformations/rotation-around-an-arbitrary-axis.html.template',
      './reference/transformations/rotation-around-an-arbitrary-axis.html'),
    @('./reference/transformations/rotation-around-an-arbitrary-axis/implicit-matrix-representation.html.template',
      './reference/transformations/rotation-around-an-arbitrary-axis/implicit-matrix-representation.html'),
    @('./reference/transformations/rotation-around-an-arbitrary-axis/explicit-matrix-representation.html.template',
      './reference/transformations/rotation-around-an-arbitrary-axis/explicit-matrix-representation.html'),
    @('./reference/transformations/axis-aligned-boxes.html.template',
      './reference/transformations/axis-aligned-boxes.html'),
    @('./reference/transformations/rays.html.template',
      './reference/transformations/rays.html'),
    @('./reference/transformations/spheres.html.template',
      './reference/transformations/spheres.html'),
    @('./reference/transformations/lines.html.template',
      './reference/transformations/lines.html'),
    @('./reference/transformations/line-segments.html.template',
      './reference/transformations/line-segments.html'),

    # Reference - Collision detection.
    @('./reference/collision-detection.html.template',
      './reference/collision-detection.html'),
    @('./reference/collision-detection/point-point.html.template',
      './reference/collision-detection/point-point.html'),
    @('./reference/collision-detection/point-sphere.html.template',
      './reference/collision-detection/point-sphere.html'),

    # Reference - Orientation representation.
    @('./reference/orientation-representation.html.template',
      './reference/orientation-representation.html'),
    @('./reference/orientation-representation/axis-angle.html.template',
      './reference/orientation-representation/axis-angle.html'),
    @('./reference/orientation-representation/quaternion.html.template',
      './reference/orientation-representation/quaternion.html'),
    @('./reference/orientation-representation/axis-angle-to-quaternion.html.template',
      './reference/orientation-representation/axis-angle-to-quaternion.html'),
    @('./reference/orientation-representation/quaternion-to-axis-angle.html.template',
      './reference/orientation-representation/quaternion-to-axis-angle.html'),
    @('./reference/orientation-representation/rotate-points-using-quaternions.html.template',
      './reference/orientation-representation/rotate-points-using-quaternions.html'),
    @('./reference/orientation-representation/axis-angle-to-matrix.html.template',
      './reference/orientation-representation/axis-angle-to-matrix.html'),
    @('./reference/orientation-representation/quaternion-to-matrix.html.template',
      './reference/orientation-representation/quaternion-to-matrix.html')
  );
