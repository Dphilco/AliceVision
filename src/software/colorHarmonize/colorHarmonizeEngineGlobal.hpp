
// Copyright (c) 2013, 2014 openMVG authors.

// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPENMVG_COLOR_HARMONIZATION_ENGINE_GLOBAL_H
#define OPENMVG_COLOR_HARMONIZATION_ENGINE_GLOBAL_H

#include <openMVG/numeric/numeric.h>
#include <openMVG/features/features.hpp>
#include <openMVG/features/RegionsPerView.hpp>
#include <openMVG/tracks/tracks.hpp>

#include <memory>

namespace openMVG {

enum EHistogramSelectionMethod
{
    eHistogramHarmonizeFullFrame     = 0,
    eHistogramHarmonizeMatchedPoints = 1,
    eHistogramHarmonizeVLDSegment    = 2,
};


class ColorHarmonizationEngineGlobal
{
public:
  ColorHarmonizationEngineGlobal(
    const std::string & sSfM_Data_Filename,
    const std::string & sMatchesPath,
    const std::string & sMatchesGeometricModel,
    const std::string & sOutDirectory,
    const std::vector<features::EImageDescriberType>& descTypes,
    int selectionMethod = -1,
    int imgRef = -1);

  ~ColorHarmonizationEngineGlobal();

  virtual bool Process();

private:

  bool CleanGraph();

  /// Read input data (point correspondences)
  bool ReadInputData();

public:

  const std::vector< std::string > & getFilenamesVector() const { return _vec_fileNames; }

  const std::vector< std::pair< size_t, size_t > > & getImagesSize() const { return _vec_imageSize; }

private:

  EHistogramSelectionMethod _selectionMethod;
  int _imgRef;
  std::string _sMatchesGeometricModel;

  // -----
  // Input data
  // ----

  std::vector< std::string > _vec_fileNames; // considered images

  features::RegionsPerView _regionsPerView;
  std::vector< std::pair< size_t, size_t > > _vec_imageSize; // Size of each image

  openMVG::matching::PairwiseMatches _pairwiseMatches; // pairwise geometric matches

  std::vector<features::EImageDescriberType> _descTypes; //< describer type use for color harmonizations

  //
  std::string _sSfM_Data_Path;// Path to the Sfm_Scene
  std::string _sMatchesPath;  // Path to correspondences and features
  std::string _sOutDirectory; // Output path where outputs will be stored
};


} // namespace openMVG

#endif // OPENMVG_COLOR_HARMONIZATION_ENGINE_GLOBAL_H
