include_directories (${CMAKE_SOURCE_DIR}/inc/)
include_directories (${CMAKE_SOURCE_DIR}/GeoAlgo/)

ROOT_GENERATE_DICTIONARY(VVDict LINKDEF LinkDef.h)

add_library (VertexReconstructionlib Analyzer.cxx DetectorObjects.cxx FillTreeVariables.cxx GetPermutations.cxx MCTruthAnalyzer.cxx PandoraAnalyzer.cxx ParticleAssociations.cxx Pi0Filter.cxx Processor.cxx Storage.cxx VertexBuilder.cxx VertexQuality.cxx VRAnalyzer.cxx VVDict.cxx)
target_link_libraries (VertexReconstructionlib GeoAlgolib ${ROOT_LIBRARIES})

message(STATUS "ROOT_LIBRARIES @: ${ROOT_LIBRARIES}")

add_executable (RunPandora RunPandora.cxx VVDict.cxx)
target_link_libraries (RunPandora VertexReconstructionlib ${ROOT_LIBRARIES})

add_executable (RunVertexReconstruction RunVertexReconstruction.cxx VVDict.cxx)
target_link_libraries (RunVertexReconstruction VertexReconstructionlib ${ROOT_LIBRARIES})

add_executable (RunVertexQuality RunVertexQuality.cxx VVDict.cxx)
target_link_libraries (RunVertexQuality VertexReconstructionlib ${ROOT_LIBRARIES})

add_executable (PrintVertexQuality PrintVertexQuality.cxx VVDict.cxx)
target_link_libraries (PrintVertexQuality ${ROOT_LIBRARIES})

add_executable (GetPermutationFiles GetPermutationFiles.cxx GetPermutations.cxx)
target_link_libraries (GetPermutationFiles ${ROOT_LIBRARIES})

add_executable (RunEvaluateVertexQuality RunEvaluateVertexQuality.cxx EvaluateVertexQuality.cxx VVDict.cxx)
target_link_libraries (RunEvaluateVertexQuality VertexReconstructionlib ${ROOT_LIBRARIES})

add_executable (RunInvDeltaMass RunInvDeltaMass.cxx VVDict.cxx)
target_link_libraries (RunInvDeltaMass VertexReconstructionlib ${ROOT_LIBRARIES})

add_executable (RunPi0Filter RunPi0Filter.cxx VVDict.cxx)
target_link_libraries (RunPi0Filter VertexReconstructionlib ${ROOT_LIBRARIES})

add_executable (RunMerge RunMerge.cxx VVDict.cxx)
target_link_libraries (RunMerge VertexReconstructionlib ${ROOT_LIBRARIES})
