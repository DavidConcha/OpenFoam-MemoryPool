# OpenFoam-MemoryPool
A drop-in memory pool for OpenFOAM that requires minimal code modifications and is compatible with various OpenFOAM flavours.

## Usage
###### Paths shown may vary by OpenFoam flavour.

Copy memoryPool.H to ```foam/containers/Lists/List/```

Add
```
#include "memoryPool.H"
```
to ```foam/containers/Lists/List/List.H```

Add (without ;) after ```#includes``` and outside the ```namespace foam```:

```
MEMORY_POOL_MACRO(scalar)
```

to ```foam/primitives/Lists/scalarList.H```

Similar with:
```
foam/primitives/Lists/tensorList.H <- MEMORY_POOL_MACRO(tensor)
foam/primitives/Lists/symmTensorList.H <- MEMORY_POOL_MACRO(symmTensor)
foam/primitives/Lists/sphericalTensorList.H <- MEMORY_POOL_MACRO(sphericalTensor)
```
For vector add, in the end of ```/foam/primitives/Vector/vector/vector.H```, outside of the ```namespace foam```:
```
MEMORY_POOL_MACRO(vector)
```

For vectorN add this lines to ```foam/primitives/Lists/VectorNList.H``` inside the ```namespace foam``` after the other similar lines in the file:

```
#define useMemPoolMacro(type, Type, args...) MEMORY_POOL_MACRO(type)
 
forAllVectorNTypes(useMemPoolMacro)
forAllTensorNTypes(useMemPoolMacro)
forAllDiagTensorNTypes(useMemPoolMacro)
forAllSphericalTensorNTypes(useMemPoolMacro)
 
#undef useMemPoolMacro
```
