/*
*
*    This program is free software; you can redistribute it and/or modify it
*    under the terms of the GNU General Public License as published by the
*    Free Software Foundation; either version 2 of the License, or (at
*    your option) any later version.
*
*    This program is distributed in the hope that it will be useful, but
*    WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software Foundation,
*    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*/

#pragma once

namespace plugmod
{
	enum CallResult: uint8_t
	{
		handled = 0,
		blocked,
		override,
	};

	// Abstract structure for sets return value
	struct callbackbase_t
	{
	public:
		void Result(CallResult result)
		{
			this->result = result;
		}

		bool IsBlocked() const
		{
			return this->result == blocked;
		}

		bool IsHandled() const
		{
			return this->result == handled;
		}

		bool IsOverride() const
		{
			return this->result == override;
		}

		CallResult GetResult() const
		{
			return this->result;
		}

	private:
		CallResult result = handled;
	};

	template <const int iCallback = 0>
	struct callback_t: public callbackbase_t
	{
	public:
		enum { k_iCallback = iCallback };
	};

} // namespace plugmod
