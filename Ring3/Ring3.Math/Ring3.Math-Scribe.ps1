$configuration='./Ring3.Math-Scribe.cfg'

# When invoking this script in a console window, the executable's paths should be prepended to the path of that console window.
# To prepend the executable's path to the path of the console window, enter
# `$env:Path = "<executable's path>;" + $env:Path`
# in the console window where
# `<executable's path>`
# is the executable's path.
$executable='PrimordialMachine.Scribe.exe'

# Generate the code for matrix operations using Scribe CAS.
for($i = 3; $i -lt 5; $i++)
{
  $scalarTypeSuffix = 'f32'
  $scalarTypeSuffixUppercase = 'F32';
  $scalarType = 'Ring2_Real32'
  $vars1 = @();

  $vars1 += "--rows=""($i)""";
  $vars1 += "--columns=""($i)""";
  $vars1 += "--scalarType=""(\""""$scalarType\"""")""";
  $vars1 += "--scalarTypeSuffix=""(\""""$scalarTypeSuffix\"""")""";
  $vars1 += "--scalarTypeSuffixUppercase=""(\""""$scalarTypeSuffixUppercase\"""")""";

  $vars = $vars1 | & {$ofs=' ';"$input"}

  Invoke-Expression "$executable cas adjugateMatrix --numberOfRows=$i --numberOfColumns=$i --pathname='./Sources/Ring3/Math/Kernels/Matrix/Adjugate$($i)x$($i)$scalarTypeSuffix.g'"
  Invoke-Expression "$executable cas matrixDeterminant --numberOfRows=$i --numberOfColumns=$i --pathname='./Sources/Ring3/Math/Kernels/Matrix/Determinant$($i)x$($i)$scalarTypeSuffix.g'"
  Invoke-Expression "$executable cas matrixTranspose --numberOfRows=$i --numberOfColumns=$i --pathname='./Sources/Ring3/Math/Kernels/Matrix/Transpose$($i)x$($i)$scalarTypeSuffix.g'"
  Invoke-Expression "$executable cas matrixAddition --numberOfRows=$i --numberOfColumns=$i --pathname='./Sources/Ring3/Math/Kernels/Matrix/Sum$($i)x$($i)$scalarTypeSuffix.g'"
  Invoke-Expression "$executable cas matrixSubtraction --numberOfRows=$i --numberOfColumns=$i --pathname='./Sources/Ring3/Math/Kernels/Matrix/Difference$($i)x$($i)$scalarTypeSuffix.g'"
  Invoke-Expression "$executable cas matrixMultiplication --numberOfRows=$i --numberOfColumns=$i --pathname='./Sources/Ring3/Math/Kernels/Matrix/Product$($i)x$($i)$scalarTypeSuffix.g'"
  Invoke-Expression "$executable cas zeroMatrix --numberOfRows=$i --numberOfColumns=$i --pathname='./Sources/Ring3/Math/Kernels/Matrix/Zero$($i)x$($i)$scalarTypeSuffix.g'"
  Invoke-Expression "$executable cas identityMatrix --numberOfRows=$i --numberOfColumns=$i --pathname='./Sources/Ring3/Math/Kernels/Matrix/Identity$($i)x$($i)$scalarTypeSuffix.g'"
  Invoke-Expression "$executable cas scalarMatrixMultiplication --numberOfRows=$i --numberOfColumns=$i --pathname='./Sources/Ring3/Math/Kernels/Matrix/ScalarMatrixProduct$($i)x$($i)$scalarTypeSuffix.g'"
}

# Generate the code for matrices using Scribe Template.
for($i = 3; $i -lt 5; $i++)
{
  $scalarTypeSuffix = 'f32'
  $scalarTypeSuffixUppercase = 'F32';
  $scalarType = 'Ring2_Real32'
  $vars1 = @();

  $vars1 += "--rows=""($i)""";
  $vars1 += "--columns=""($i)""";
  $vars1 += "--scalarType=""(\""""$scalarType\"""")""";
  $vars1 += "--scalarTypeSuffix=""(\""""$scalarTypeSuffix\"""")""";
  $vars1 += "--scalarTypeSuffixUppercase=""(\""""$scalarTypeSuffixUppercase\"""")""";

  $vars = $vars1 | & {$ofs=' ';"$input"}

  Invoke-Expression "$executable template $vars $configuration './Sources/Ring3/Math/Matrix-v2.c.t' './Sources/Ring3/Math/Matrix$($i)x$($i)$scalarTypeSuffix.c'"
  Invoke-Expression "$executable template $vars $configuration './Sources/Ring3/Math/Matrix-v2.h.t' './Sources/Ring3/Math/Matrix$($i)x$($i)$scalarTypeSuffix.h'"
}

# Matrix-direction and matrix-point multiplication.
for ($i = 2; $i -lt 5; $i++)
{
  # Multiply an $n \times n$ matrix and a $n$ vector (v_1,...,v_{n})
  #Invoke-Expression "$executable cas matrixVectorMultiplication --numberOfElements=$i --pathname='./Sources/Ring3/Math/Transformations/MatrixVectorProduct$($i)F64.g'"
  # Multiply a $n \times n$ matrix and $n$ direction vector (v_1,...,v_{n-1},0).
  #Invoke-Expression "$executable cas matrixDirectionMultiplication --numberOfElements=$i --pathname='./Sources/Ring3/Math/Transformations/MatrixDirectionProduct$($i)F64.g'"
  # Multiply a $n \times n$ matrix and $n$ position vector (v_1,...,v_{n-1},1).
  #Invoke-Expression "$executable cas matrixPositionMultiplication --numberOfElements=$i --pathname='./Sources/Ring3/Math/Transformations/MatrixPositionProduct$($i)F64.g'"
}

# Generate the code for vector operations using Scribe CAS.
for($i = 2; $i -lt 5; $i++)
{
  $scalarTypeSuffix = 'f32'
  $scalarTypeSuffixUppercase = 'F32';
  $scalarType = 'Ring2_Real32'
  $vars1 = @();

  $vars1 += "--dimensionality=""($i)""";
  $vars1 += "--scalarType=""(\""""$scalarType\"""")""";
  $vars1 += "--scalarTypeSuffix=""(\""""$scalarTypeSuffix\"""")""";
  $vars1 += "--scalarTypeSuffixUppercase=""(\""""$scalarTypeSuffixUppercase\"""")""";

  $vars = $vars1 | & {$ofs=' ';"$input"}

  Invoke-Expression "$executable template $vars $configuration './Sources/Ring3/Math/Vector.c.t' './Sources/Ring3/Math/Vector$($i)$scalarTypeSuffix.c'"
  Invoke-Expression "$executable template $vars $configuration './Sources/Ring3/Math/Vector.h.t' './Sources/Ring3/Math/Vector$($i)$scalarTypeSuffix.h'"

  #Invoke-Expression "$executable cas vectorAddition --numberOfElements=$i --pathname='./Sources/Ring3/Math/Kernels/Sum$($i)F64.g'"
  #Invoke-Expression "$executable cas vectorSubtraction --numberOfElements=$i --pathname='./Sources/Ring3/Math/Kernels/Difference$($i)F64.g'"
  #Invoke-Expression "$executable cas dotProduct --numberOfElements=$i --pathname='./Sources/Ring3/Math/Kernels/DotProduct$($i)F64.g'"
  #Invoke-Expression "$executable cas zeroVector --numberOfElements=$i --pathname='./Sources/Ring3/Math/Kernels/Zero$($i)F64.g'"
  #Invoke-Expression "$executable cas scalarVectorMultiplication --numberOfElements=$i --pathname='./Sources/Ring3/Math/Kernels/ScalarVectorProduct$($i)F64.g'"
  #Invoke-Expression "$executable cas vectorVectorMultiplication --numberOfElements=$i --pathname='./Sources/Ring3/Math/Kernels/VectorVectorProduct$($i)F64.g'"
  #Invoke-Expression "$executable cas vectorVectorDivision --numberOfElements=$i --pathname='./Sources/Ring3/Math/Kernels/VectorVectorQuotient$($i)F64.g'"
}

for($i = 2; $i -lt 4; $i++)
{
  $scalarTypeSuffix = 'f32'
  $scalarTypeSuffixUppercase = 'F32';
  $scalarType = 'Ring2_Real32'
  $vars1 = @();

  $vars1 += "--dimensionality=""($i)""";
  $vars1 += "--scalarType=""(\""""$scalarType\"""")""";
  $vars1 += "--scalarTypeSuffix=""(\""""$scalarTypeSuffix\"""")""";
  $vars1 += "--scalarTypeSuffixUppercase=""(\""""$scalarTypeSuffixUppercase\"""")""";

  $vars = $vars1 | & {$ofs=' ';"$input"}

  # Rays.
  Invoke-Expression "$executable template $vars $configuration './Sources/Ring3/Math/Ray.c.t' './Sources/Ring3/Math/Ray$($i)$scalarTypeSuffix.c'"
  Invoke-Expression "$executable template $vars $configuration './Sources/Ring3/Math/Ray.h.t' './Sources/Ring3/Math/Ray$($i)$scalarTypeSuffix.h'"

  # Spheres.
  Invoke-Expression "$executable template $vars $configuration './Sources/Ring3/Math/Sphere.c.t' './Sources/Ring3/Math/Sphere$($i)$scalarTypeSuffix.c'"
  Invoke-Expression "$executable template $vars $configuration './Sources/Ring3/Math/Sphere.h.t' './Sources/Ring3/Math/Sphere$($i)$scalarTypeSuffix.h'"

  # Lines.
  #Invoke-Expression "$executable template --dimensionality=""($i)"" --type=""(\""""F64\"""")"" $configuration './Line.c.t' './Mkx/Math/Line$($i)F64.c'"
  #Invoke-Expression "$executable template --dimensionality=""($i)"" --type=""(\""""F64\"""")"" $configuration './Line.h.t' './Mkx/Math/Line$($i)F64.h'"

  # Line Segment.
  #Invoke-Expression "$executable template --dimensionality=""($i)"" --type=""(\""""F64\"""")"" $configuration './LineSegment.c.t' './Mkx/Math/LineSegment$($i)F64.c'"
  #Invoke-Expression "$executable template --dimensionality=""($i)"" --type=""(\""""F64\"""")"" $configuration './LineSegment.h.t' './Mkx/Math/LineSegment$($i)F64.h'"

  # Axis aligned boxes.
  #Invoke-Expression "$executable template --dimensionality=""($i)"" --type=""(\""""F64\"""")"" $configuration './AxisAlignedBox.c.t' './Mkx/Math/AxisAlignedBox$($i)F64.c'"
  #Invoke-Expression "$executable template --dimensionality=""($i)"" --type=""(\""""F64\"""")"" $configuration './AxisAlignedBox.h.t' './Mkx/Math/AxisAlignedBox$($i)F64.h'"
  #Invoke-Expression "$executable template --dimensionality=""($i)"" --type=""(\""""F64\"""")"" $configuration './AxisAlignedBoxBuilder.c.t' './Mkx/Math/AxisAlignedBoxBuilder$($i)F64.c'"
  #Invoke-Expression "$executable template --dimensionality=""($i)"" --type=""(\""""F64\"""")"" $configuration './AxisAlignedBoxBuilder.h.t' './Mkx/Math/AxisAlignedBoxBuilder$($i)F64.h'"
}
