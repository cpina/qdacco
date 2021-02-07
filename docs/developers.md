# Developer documentation
## How to update qdacco translation files
Please note that `lrelease` step should be part of the building process instead of having the file pushed into git (see [issue #5](https://github.com/cpina/qdacco/issues/5)].

At the moment in `gui/` do:
```sh
lupdate *.cpp *.ui *.h ../nongui/*.cpp ../nongui/*.h -ts qdacco_ca.ts
linguist qdacco_ca.ts
lrelease qdacco_ca.ts -qm qdacco_ca.qm
```
And commit the files that have changed.

## How to release a new version
 * Make sure that translation files do not need to be updated
 * Update `QDACCO_VERSION` in `CMakeLists.txt`
 * If needed update the copyright_date in `gui/AuxiliarGUI.cpp` (see [issue #6](//github.com/cpina/qdacco/issues/6) to move this into `CMakeLists.txt`)
 * Update `changelog` file with the new notes
 * `git commit` of latest changes; `git push`
 * Open https://github.com/cpina/qdacco/releases , click on "Draft a new release" and write the information:
   * Tag version: same as QDACCO_VERSION **prepended by v** (e.g. v1.0.2)
   * Write a release title
   * Click on `Publish release`
