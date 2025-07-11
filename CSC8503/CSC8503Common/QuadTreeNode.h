#pragma once
#include "../../Common/Vector3.h"
#include "CollisionDetection.h"
#include <functional>
#include <list>
namespace NCL {
	using namespace Maths;
	namespace CSC8503 {
		template <class T>
		class QuadTree;
		template <class T>
		struct QuadTreeEntry {
			Vector3 pos;
			Vector3 size;//����2D
			T object;
			
				QuadTreeEntry(T obj, Vector3 pos, Vector3 size) {
				object = obj;
				this-> pos = pos;
				this-> size = size;
				
			}
			
		};
		
		template <class T>
		class QuadTreeNode {
		public:
				typedef std::function<void(std::list<QuadTreeEntry<T>>&)> QuadTreeFunc;

				void OperateOnContents(QuadTreeFunc* func) {
					if (children) {
						for (size_t i = 0; i < 4; i++)
						{
							children[i].OperateOnContents(func);
						}
					}
					else {
						if (!contents.empty()) {
							func(contents);
						}
					}
					
				}

				void Split() {
					Vector2 halfsize = size / 2.0f;
					children = new QuadTreeNode<T>[4];
					children[0] = QuadTreeNode<T>(position + Vector2(-halfsize.x, halfsize.y), halfsize);
					children[1] = QuadTreeNode<T>(position + Vector2(halfsize.x, halfsize.y), halfsize);
					children[2] = QuadTreeNode<T>(position + Vector2(-halfsize.x, -halfsize.y), halfsize);
					children[3] = QuadTreeNode<T>(position + Vector2(halfsize.x, -halfsize.y), halfsize);
				}

				void Insert(T & object, const Vector3 & objectPos,
					const Vector3 & objectSize, int depthLeft, int maxSize) {
					if (!CollisionDetection::AABBTest(objectPos,
						Vector3(position.x, 0, position.y), objectSize,
						Vector3(size.x, 1000.0f, size.y))) {
						return;
					}//������� 
					if (children) { // not a leaf node , just descend the tree
						for (int i = 0; i < 4; ++i) {
							children[i].Insert(object, objectPos, objectSize,
								depthLeft - 1, maxSize);
							
						}
						
					}
					else { // currently a leaf node , can just expand
						contents.push_back(QuadTreeEntry <T >(object, objectPos, objectSize));
						if ((int)contents.size() > maxSize && depthLeft > 0) {
							if (!children) {
								Split();
								// we need to reinsert the contents so far !
									for (const auto& i : contents) {
									for (int j = 0; j < 4; ++j) {
										auto entry = i;
										children[j].Insert(entry.object, entry.pos,
											entry.size, depthLeft - 1, maxSize);
								
									}
								
								}
								contents.clear(); // contents now distributed !
								
							}
						
						}
					}
					
				}

		protected:
				friend class QuadTree <T>;
				
				QuadTreeNode() {}
				QuadTreeNode(Vector2 pos, Vector2 size) {
				children = nullptr;
				this-> position = pos;
				this-> size = size;
				}
				~QuadTreeNode() { delete[] children; }
		protected:
				std::list<QuadTreeEntry<T>> contents;
			
				Vector2 position;
				Vector2 size;
			
				QuadTreeNode <T >*children;
			
		};
	}
}

