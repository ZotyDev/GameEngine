#pragma once

namespace UE
{
	template<typename T>
	class DynamicTree
	{
	public:
		DynamicTree()
			: Element()
		{
			UpdateIterators(0);
		}

		DynamicTree(const T& element)
			: Element(element)
		{
			UpdateIterators(0);
		}

		UEUint32 Size()
		{
			return m_Branches.size();
		}

		UEUint32 GetTraverseIndex()
		{
			return m_aux_traverse_iterator - m_aux_begin_iterator;
		}

		UEResult SetEachFn(std::function<UEResult(DynamicTree<T>*, DynamicTree<T>*)> f)
		{
			m_EachFunction = f;

			return UEResult::Success;
		}

		UEResult Each()
		{
			UpdateIterators(0);
			while (m_aux_traverse_iterator != m_aux_end_iterator)
			{
				if (m_EachFunction(this, &*m_aux_traverse_iterator) == UEResult::Error)
				{
					UE_CORE_ERROR("Dynamic Tree Each() failed: function returned error");
					return UEResult::Error;
				}

				if (m_ShouldIncrement)
				{
					m_aux_traverse_iterator++;
				}
				else
				{
					m_ShouldIncrement = true;
				}
			}

			return UEResult::Success;
		}

		void PushBack(const DynamicTree<T>& element)
		{
			UEUint32 CurrentTraverseIndex = m_aux_traverse_iterator - m_aux_begin_iterator;
			m_Branches.push_back(element);

			UpdateIterators(CurrentTraverseIndex);
		}

		void PushFront(const DynamicTree<T>& element)
		{
			UEUint32 CurrentTraverseIndex = m_aux_traverse_iterator - m_aux_begin_iterator;
			m_Branches.insert(m_Branches.begin(), element);

			UpdateIterators(CurrentTraverseIndex);
		}

		void PopBack()
		{
			UEUint32 CurrentTraverseIndex = m_aux_traverse_iterator - m_aux_begin_iterator;
			m_Branches.pop_back();

			UpdateIterators(CurrentTraverseIndex);
			m_ShouldIncrement = false;
		}

		void PopFront()
		{
			UEUint32 CurrentTraverseIndex = m_aux_traverse_iterator - m_aux_begin_iterator;
			m_Branches.erase(m_aux_begin_iterator);

			UpdateIterators(CurrentTraverseIndex);
			m_ShouldIncrement = false;
		}

		const T& Back()
		{
			return m_Branches.back();
		}

		const T& Front()
		{
			return m_Branches.front();
		}

		void Insert(const DynamicTree<T>& element, UEUint32 index)
		{
			UEUint32 CurrentTraverseIndex = m_aux_traverse_iterator - m_aux_begin_iterator;
			m_Branches.insert(m_Branches.begin() + index, element);

			UpdateIterators(CurrentTraverseIndex);
		}

		void Erase(UEUint32 index)
		{
			UEUint32 CurrentTraverseIndex = m_aux_traverse_iterator - m_aux_begin_iterator;
			m_Branches.erase(m_Branches.begin() + index);

			UpdateIterators(CurrentTraverseIndex);
			m_ShouldIncrement = false;
		}

		void EraseAtTraverse()
		{
			Erase(m_aux_traverse_iterator - m_Branches.begin());
		}

		void OrderedSwap(UEUint32 firstElementIndex, UEUint32 secondElementIndex)
		{
			/* Hey, future reader
				*  This is a WARNING!!!
				*  Treat this piece of code as if it is the holy bible
				*  Don't change it!!!
				*  The inner workings of this are almost magical, Idk why but sometimes it works, sometimes don't
				*  SO, you should approach this only if you know what you are doing (wich I don't)
				*/
			if (firstElementIndex != secondElementIndex)
			{
				if (firstElementIndex < secondElementIndex)
				{
					std::vector<DynamicTree<T>>::iterator t_aux_swap_source_iterator = m_aux_begin_iterator + secondElementIndex;
					std::vector<DynamicTree<T>>::iterator t_aux_swap_target_iterator = m_aux_begin_iterator + firstElementIndex;

					// Rotate by 1 to left the range between current element and moved element
					std::rotate(
						t_aux_swap_target_iterator,
						t_aux_swap_source_iterator,
						t_aux_swap_source_iterator + 1
					);
				}
				else
				{
					std::vector<DynamicTree<T>>::reverse_iterator t_aux_reverse_end_iterator = m_Branches.rend();
					std::vector<DynamicTree<T>>::reverse_iterator t_aux_reverse_swap_source_iterator = t_aux_reverse_end_iterator - secondElementIndex;
					std::vector<DynamicTree<T>>::reverse_iterator t_aux_reverse_swap_target_iterator = t_aux_reverse_end_iterator - firstElementIndex;

					// What the fuck did you just bring upon this cursed land?
					// Rotate by 1 to right the range between current element and moved element
					std::rotate(
						t_aux_reverse_swap_target_iterator,
						t_aux_reverse_swap_source_iterator - 1,
						t_aux_reverse_swap_source_iterator
					);
				}
			}
		}

		typename std::vector<DynamicTree<T>>::iterator begin() { return m_Branches.begin(); }
		typename std::vector<DynamicTree<T>>::iterator end() { return m_Branches.end(); }
		typename std::vector<DynamicTree<T>>::reverse_iterator rbegin() { return m_Branches.rbegin(); }
		typename std::vector<DynamicTree<T>>::reverse_iterator rend() { return m_Branches.rend(); }

		typename std::vector<DynamicTree<T>>::const_iterator begin() const { return m_Branches.begin(); }
		typename std::vector<DynamicTree<T>>::const_iterator end() const { return m_Branches.end(); }
		typename std::vector<DynamicTree<T>>::const_reverse_iterator rbegin() const { return m_Branches.rbegin(); }
		typename std::vector<DynamicTree<T>>::const_reverse_iterator rend() const { return m_Branches.rend(); }

	private:
		void UpdateIterators(UEUint32 traverseIndex)
		{
			m_aux_begin_iterator = m_Branches.begin();
			m_aux_end_iterator = m_Branches.end();
			m_aux_traverse_iterator = m_aux_begin_iterator + traverseIndex;
		}

	public:
		T Element;

	private:
		typename std::vector<DynamicTree<T>> m_Branches;
		typename std::vector<DynamicTree<T>>::iterator m_aux_begin_iterator;
		typename std::vector<DynamicTree<T>>::iterator m_aux_end_iterator;
		typename std::vector<DynamicTree<T>>::iterator m_aux_traverse_iterator;
		UEBool m_ShouldIncrement = true;

	private:
		typename std::function<UEResult(DynamicTree<T>*, DynamicTree<T>*)> m_EachFunction;
	};
}