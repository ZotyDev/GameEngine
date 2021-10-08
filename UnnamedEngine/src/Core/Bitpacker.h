#pragma once

namespace UE
{
	class Bitpacker
	{
	public:
		Bitpacker();
		~Bitpacker();

		template<typename T>
		Bitpacker& operator << (T data)
		{
			WriteBitStream(data, CalculateRequiredBits(data), m_Packer, m_Index, m_RawData);

			UE_CORE_TRACE(CalculateRequiredBits(data));

			return *this;
		}

		template<typename T>
		Bitpacker& operator >> (T& data)
		{
			return *this;
		}

		Bitpacker& operator << (UEBool data);
		Bitpacker& operator >> (UEBool& data);

	private:
		std::string toBinary(UEUint64 n)
		{
			std::string r;
			while (n != 0) { r = (n % 2 == 0 ? "0" : "1") + r; n /= 2; }
			return r;
		}

		template<typename T>
		UEUint8 CalculateRequiredBits(T data)
		{
			// Check if data equals to 1 or 0
			UEUint64 ToBeTested = UEUint64(data);
			if (ToBeTested == 0 || ToBeTested == 1)
			{
				return 1;
			}

			// UEUint64 Tester1 = 0xAAAAAAAAAAAAAAAA;
			// UEUint64 Tester2 = 0xCCCCCCCCCCCCCCCC;
			// UEUint64 Tester3 = 0xF0F0F0F0F0F0F0F0;
			// UEUint64 Tester4 = 0xFF00FF00FF00FF00;
			// UEUint64 Tester5 = 0xFFFF0000FFFF0000;
			// UEUint64 Tester6 = 0xFFFFFFFF00000000;

			UEUint8 RequiredBits = 1;
			RequiredBits += (ToBeTested & 0xAAAAAAAAAAAAAAAA) ? 1  : 0;
			RequiredBits += (ToBeTested & 0xCCCCCCCCCCCCCCCC) ? 2  : 0;
			RequiredBits += (ToBeTested & 0xF0F0F0F0F0F0F0F0) ? 4  : 0;
			RequiredBits += (ToBeTested & 0xFF00FF00FF00FF00) ? 8  : 0;
			RequiredBits += (ToBeTested & 0xFFFF0000FFFF0000) ? 16 : 0;
			RequiredBits += (ToBeTested & 0xFFFFFFFF00000000) ? 32 : 0;

			return RequiredBits;
		}

		void FlushTarget(UEUint64& target, UEUint8& targetSize, std::vector<UEUint64>& container)
		{
			container.push_back(target);
			target = 0;
			targetSize = 0;
		}

		template<typename T>
		void WriteBitStream(T source, UEUint8 size, UEUint64& target, UEUint8& targetSize, std::vector<UEUint64>& container)
		{
			// check if overflow needs to be used
			if (targetSize + size > 64)
			{
				T Holder = source;
				
				// calculate how many bits fit inside target
				UEUint8 PossibleAtOverflow = (targetSize + size) - 64;
				UEUint8 PossibleAtTarget = size - PossibleAtOverflow;

				// resume holder to possible bits only
				Holder >>= PossibleAtOverflow;

				// shift target to left by the possbile bits
				target <<= PossibleAtTarget;

				// put the possible bits inside target
				target |= Holder;

				FlushTarget(target, targetSize, container);

				// get rid of already packed bits
				Holder = source;
				Holder <<= PossibleAtTarget;
				Holder >>= PossibleAtTarget;

				// put the remaining bits into target
				target |= Holder;

				return;
			}
			else
			{
				// shift target to left by the size
				target <<= size;
			}

			// put bits inside target
			target |= source;

			// increment target size
			targetSize += size;

			// check if target is full
			if (targetSize == 64)
			{
				FlushTarget(target, targetSize, container);
			}
		}

	private:
		UEUint64 m_Packer = 0;
		UEUint8 m_Index = 0;
		UEUint64 m_Counter = 0;

		std::vector<UEUint64> m_RawData;
	};
}