//split this here so modifying GraphAligner.h doesn't require recompiling every cpp file

#include <limits>
#include "GraphAlignerWrapper.h"
#include "GraphAligner.h"
#include "ThreadReadAssertion.h"

AlignmentResult AlignOneWay(const AlignmentGraph& graph, const std::string& seq_id, const std::string& sequence, size_t alignmentBandwidth, bool quietMode, GraphAlignerCommon<size_t, int32_t, uint64_t>::AlignerGraphsizedState& reusableState, double preciseClippingIdentityCutoff, int Xdropcutoff, size_t DPRestartStride)
{
	GraphAlignerCommon<size_t, int32_t, uint64_t>::Params params {alignmentBandwidth, graph, std::numeric_limits<size_t>::max(), quietMode, false, 1, 0, preciseClippingIdentityCutoff, Xdropcutoff, 0};
	GraphAligner<size_t, int32_t, uint64_t> aligner {params};
	return aligner.AlignOneWay(seq_id, sequence, reusableState, DPRestartStride);
}

AlignmentResult AlignMultiseed(const AlignmentGraph& graph, const std::string& seq_id, const std::string& sequence, size_t alignmentBandwidth, size_t maxCellsPerSlice, bool quietMode, bool sloppyOptimizations, const std::vector<SeedHit>& seedHits, GraphAlignerCommon<size_t, int32_t, uint64_t>::AlignerGraphsizedState& reusableState, size_t minClusterSize, double seedExtendDensity, double preciseClippingIdentityCutoff, int Xdropcutoff, double multimapScoreFraction)
{
	GraphAlignerCommon<size_t, int32_t, uint64_t>::Params params {alignmentBandwidth, graph, maxCellsPerSlice, quietMode, sloppyOptimizations, minClusterSize, seedExtendDensity, preciseClippingIdentityCutoff, Xdropcutoff, multimapScoreFraction};
	GraphAligner<size_t, int32_t, uint64_t> aligner {params};
	return aligner.AlignMultiseed(seq_id, sequence, seedHits, reusableState);
}

AlignmentResult AlignOneWay(const AlignmentGraph& graph, const std::string& seq_id, const std::string& sequence, size_t alignmentBandwidth, size_t maxCellsPerSlice, bool quietMode, bool sloppyOptimizations, const std::vector<SeedHit>& seedHits, GraphAlignerCommon<size_t, int32_t, uint64_t>::AlignerGraphsizedState& reusableState, size_t minClusterSize, double seedExtendDensity, double preciseClippingIdentityCutoff, int Xdropcutoff)
{
	GraphAlignerCommon<size_t, int32_t, uint64_t>::Params params {alignmentBandwidth, graph, maxCellsPerSlice, quietMode, sloppyOptimizations, minClusterSize, seedExtendDensity, preciseClippingIdentityCutoff, Xdropcutoff, 0};
	GraphAligner<size_t, int32_t, uint64_t> aligner {params};
	return aligner.AlignOneWay(seq_id, sequence, seedHits, reusableState);
}

void AddAlignment(const std::string& seq_id, const std::string& sequence, AlignmentResult::AlignmentItem& alignment)
{
	GraphAlignerCommon<size_t, int32_t, uint64_t>::Params params {1, AlignmentGraph::DummyGraph(), 1, true, true, 1, 0, .5, 0, 0};
	GraphAligner<size_t, int32_t, uint64_t> aligner {params};
	aligner.AddAlignment(seq_id, sequence, alignment);
}

void AddGAFLine(const AlignmentGraph& graph, const std::string& seq_id, const std::string& sequence, AlignmentResult::AlignmentItem& alignment, bool cigarMatchMismatchMerge)
{
	GraphAlignerCommon<size_t, int32_t, uint64_t>::Params params {1, graph, 1, true, true, 1, 0, .5, 0, 0};
	GraphAligner<size_t, int32_t, uint64_t> aligner {params};
	aligner.AddGAFLine(seq_id, sequence, alignment, cigarMatchMismatchMerge);
}

void AddCorrected(AlignmentResult::AlignmentItem& alignment)
{
	GraphAlignerCommon<size_t, int32_t, uint64_t>::Params params {1, AlignmentGraph::DummyGraph(), 1, true, true, 1, 0, .5, 0, 0};
	GraphAligner<size_t, int32_t, uint64_t> aligner {params};
	aligner.AddCorrected(alignment);
}

void OrderSeeds(const AlignmentGraph& graph, std::vector<SeedHit>& seedHits)
{
	GraphAlignerCommon<size_t, int32_t, uint64_t>::Params params {1, graph, 1, true, true, 1, 0, .5, 0, 0};
	GraphAligner<size_t, int32_t, uint64_t> aligner {params};
	aligner.orderSeedsByChaining(seedHits);
}

void PrepareMultiseeds(const AlignmentGraph& graph, std::vector<SeedHit>& seedHits, const size_t seqLen)
{
	GraphAlignerCommon<size_t, int32_t, uint64_t>::Params params {1, graph, 1, true, true, 1, 0, .5, 0, 0};
	GraphAligner<size_t, int32_t, uint64_t> aligner {params};
	seedHits = aligner.prepareSeedsForMultiseeding(seedHits, seqLen);
}
