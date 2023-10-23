#pragma once
#include <Siv3D.hpp>

namespace dss
{
	class InputSet
	{
	public:
		InputGroup left;
		InputGroup right;
		InputGroup up;
		InputGroup down;

		Vec2 leftStick = Vec2::Zero();

		InputGroup apply;
		InputGroup cancel;
		InputGroup pause;


		const InputSet operator +(const InputSet& input) const
		{
			InputSet result;

			result.left = { this->left | input.left };
			result.right = { this->right | input.right };
			result.up = { this->up | input.up };
			result.down = { this->down | input.down };

			if (this->leftStick.isZero())
			{
				result.leftStick = input.leftStick;
			}
			else
			{
				result.leftStick = this->leftStick;
			}

			result.apply = { this->apply | input.apply };
			result.cancel = { this->cancel | input.cancel };
			result.pause = { this->pause | input.pause };

			return result;
		}

		InputSet& operator+=(const InputSet& input)
		{
			this->left = { this->left | input.left };
			this->right = { this->right | input.right };
			this->up = { this->up | input.up };
			this->down = { this->down | input.down };

			if (this->leftStick.isZero())
			{
				this->leftStick = input.leftStick;
			}

			this->apply = { this->apply | input.apply };
			this->cancel = { this->cancel | input.cancel };
			this->pause = { this->pause | input.pause };

			return *this;
		}
	};
}
