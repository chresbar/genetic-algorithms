#include "graph.h"

unsigned Graph::addEdge(const Edge& edge)
{
    if (!edge.mDirected)
        mVertices[edge.mEnd].insert(edge.mBegin);

    mVertices[edge.mBegin].insert(edge.mEnd);
    mEdges.emplace(mEdgeCounter, edge);
    return mEdgeCounter++;
}
