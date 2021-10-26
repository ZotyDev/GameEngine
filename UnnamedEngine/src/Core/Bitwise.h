#pragma once

namespace UE
{
	template<typename T>
	UEUint8 CalculateRequiredBits(T data)
	{
		UEUint64 ToBeTested = ((UEUint64)data);
		UEUint8 RequiredBits = 1;

		if (ToBeTested >> 32)
		{
			RequiredBits += 32;
			ToBeTested >>= 32;
		}

		if (ToBeTested >> 16)
		{
			RequiredBits += 16;
			ToBeTested >>= 16;
		}

		if (ToBeTested >> 8)
		{
			RequiredBits += 8;
			ToBeTested >>= 8;
		}

		if (ToBeTested >> 4)
		{
			RequiredBits += 4;
			ToBeTested >>= 4;
		}

		if (ToBeTested >> 2)
		{
			RequiredBits += 2;
			ToBeTested >>= 2;
		}

		if (ToBeTested - 1)
		{
			RequiredBits++;
		}

		return RequiredBits;
	}

	template<typename T>
	UEUint8 CountBits(T data)
	{
		return CalculateRequiredBits(data);
	}

	UEResult ReadBinaryStream(UEUint64 target, UEUint8 position, UEUint8 wordSize, UEUint64& buffer);
	UEResult WriteBinaryStream(UEUint64& target, UEUint8 position, UEUint8 wordSize, UEUint64 buffer);
	void FlushBinaryStream(UEUint64& target, UEUint8& targetPosition, std::deque<UEUint64>& container);

	std::string ToBinary(UEUint64 n);
	std::string ToBinaryF(UEUint64 n);

	template<typename T>
	void WriteBitStream(T source, UEUint8 size, UEUint64& target, UEUint8& targetPosition, std::deque<UEUint64>& container)
	{
		// calculate total size after operation
		UEUint8 EndPosition = targetPosition + size;

		// check if there is enough space for the insert
		if (EndPosition <= 65)
		{
			// insert data at position
			WriteBinaryStream(target, targetPosition, size, (UEUint64)source);			
			targetPosition += size;

			// check if target is full
			if (targetPosition == 65)
			{
				FlushBinaryStream(target, targetPosition, container);
			}
		}
		else
		{
			// calculate sizes
			UEUint8 BitsAtOverflow = EndPosition - 65; 
			UEUint8 BitsAtTarget = size - BitsAtOverflow;

			// resume data to fit inside target
			UEUint64 Holder = (UEUint64)source;
			Holder >>= BitsAtOverflow;

			// insert data at position
			WriteBinaryStream(target, targetPosition, BitsAtTarget, Holder);

			// flush target
			FlushBinaryStream(target, targetPosition, container);

			// resume remaining data to fit inside overflow
			Holder = (UEUint64)source;
			Holder <<= 64 - BitsAtOverflow;
			Holder >>= 64 - BitsAtOverflow;

			// insert data at position
			WriteBinaryStream(target, targetPosition, BitsAtOverflow, Holder);
			targetPosition += BitsAtOverflow;
		}
	}

	template<typename T>
	UEResult ReadBitStream(T& target, UEUint8& targetPosition, UEUint8 size, std::deque<UEUint64>& container)
	{
		// check if there is data inside container
		if (container.size() < 1)
		{
			UE_CORE_ERROR("Failed to read bit stream: container is empty");
			return UEResult::Error;
		}

		// calculate where operation will end
		UEUint8 EndPosition = targetPosition + size;

		// check for edge case
		if (targetPosition == 65)
		{
			// pop first block from container since it is empty
			container.pop_front();

			// start position again
			targetPosition = 1;

			// read block from container
			UEUint64 Block = container.front();

			// read data from block
			UEUint64 Holder = 0;
			ReadBinaryStream(Block, targetPosition, size, Holder);

			// return data
			target = (T)Holder;
			targetPosition += size;
			return UEResult::Success;
		}

		// check if the read position and size is valid
		if (EndPosition <= 65)
		{
			// read block from container
			UEUint64 Block = container.front();

			// read data from block
			UEUint64 Holder = 0;
			ReadBinaryStream(Block, targetPosition, size, Holder);

			// return data
			target = (T)Holder;
			targetPosition += size;
		}
		else
		{
			if (container.size() > 1)
			{
				// calculate sizes
				UEUint8 BitsAtOverflow = EndPosition - 65;
				UEUint8 BitsAtTarget = size - BitsAtOverflow;

				// read block from container
				UEUint64 Block = container.front();

				// delete block from container since it is no longer needed
				container.pop_front();

				// read data from block
				UEUint64 FirstHolder = 0;
				ReadBinaryStream(Block, targetPosition, BitsAtTarget, FirstHolder);

				// shift data to accommodate the rest of it
				FirstHolder <<= BitsAtOverflow;

				// read another block from container
				Block = container.front();

				// read data again
				UEUint64 SecondHolder = 0;
				targetPosition = 1;
				ReadBinaryStream(Block, targetPosition, BitsAtOverflow, SecondHolder);
				
				// merge and return data
				FirstHolder |= SecondHolder;
				target = (T)FirstHolder;
				targetPosition += BitsAtOverflow;
			}
			else
			{
				UE_CORE_ERROR("Failed to read bit stream: inserted position {0} and/or size {0} is invalid", targetPosition, size);
				return UEResult::Error;
			}
		}
	}
}