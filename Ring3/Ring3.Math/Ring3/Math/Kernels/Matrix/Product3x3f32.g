beginMatrix()
setMatrixElement(0, 0, getMatrixElement(a, 0, 0) * getMatrixElement(b, 0, 0) + getMatrixElement(a, 0, 1) * getMatrixElement(b, 1, 0) + getMatrixElement(a, 0, 2) * getMatrixElement(b, 2, 0))
setMatrixElement(0, 1, getMatrixElement(a, 0, 0) * getMatrixElement(b, 0, 1) + getMatrixElement(a, 0, 1) * getMatrixElement(b, 1, 1) + getMatrixElement(a, 0, 2) * getMatrixElement(b, 2, 1))
setMatrixElement(0, 2, getMatrixElement(a, 0, 0) * getMatrixElement(b, 0, 2) + getMatrixElement(a, 0, 1) * getMatrixElement(b, 1, 2) + getMatrixElement(a, 0, 2) * getMatrixElement(b, 2, 2))
setMatrixElement(1, 0, getMatrixElement(a, 1, 0) * getMatrixElement(b, 0, 0) + getMatrixElement(a, 1, 1) * getMatrixElement(b, 1, 0) + getMatrixElement(a, 1, 2) * getMatrixElement(b, 2, 0))
setMatrixElement(1, 1, getMatrixElement(a, 1, 0) * getMatrixElement(b, 0, 1) + getMatrixElement(a, 1, 1) * getMatrixElement(b, 1, 1) + getMatrixElement(a, 1, 2) * getMatrixElement(b, 2, 1))
setMatrixElement(1, 2, getMatrixElement(a, 1, 0) * getMatrixElement(b, 0, 2) + getMatrixElement(a, 1, 1) * getMatrixElement(b, 1, 2) + getMatrixElement(a, 1, 2) * getMatrixElement(b, 2, 2))
setMatrixElement(2, 0, getMatrixElement(a, 2, 0) * getMatrixElement(b, 0, 0) + getMatrixElement(a, 2, 1) * getMatrixElement(b, 1, 0) + getMatrixElement(a, 2, 2) * getMatrixElement(b, 2, 0))
setMatrixElement(2, 1, getMatrixElement(a, 2, 0) * getMatrixElement(b, 0, 1) + getMatrixElement(a, 2, 1) * getMatrixElement(b, 1, 1) + getMatrixElement(a, 2, 2) * getMatrixElement(b, 2, 1))
setMatrixElement(2, 2, getMatrixElement(a, 2, 0) * getMatrixElement(b, 0, 2) + getMatrixElement(a, 2, 1) * getMatrixElement(b, 1, 2) + getMatrixElement(a, 2, 2) * getMatrixElement(b, 2, 2))
endMatrix()
