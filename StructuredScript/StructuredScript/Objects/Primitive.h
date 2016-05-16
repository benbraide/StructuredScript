#pragma once

#ifndef STRUCTURED_SCRIPT_PRIMITIVE_OBJECT_H
#define STRUCTURED_SCRIPT_PRIMITIVE_OBJECT_H

#include "../Common/ExceptionManagerQuery.h"
#include "../Common/ObjectQuery.h"
#include "../Common/Factory.h"

#include "../Interfaces/Objects/IPrimitiveObject.h"
#include "../Interfaces/Types/IPrimitiveType.h"

namespace StructuredScript{
	namespace Objects{
		class Primitive : public IAny, public IPrimitiveObject{
		public:
			explicit Primitive(IType::Ptr type)
				: type_(type){}

			virtual Ptr ptr() override;

			virtual Ptr clone(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr cast(IType::Ptr type, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr base() override;

			virtual IType::Ptr type() override;

			virtual void setMemory(IMemory *memory) override;

			virtual IMemory *memory() override;

			virtual bool truth(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual std::string str(IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual Ptr evaluateLeftUnary(const std::string &value, IExceptionManager *exception, INode *expr) override;

			virtual Ptr evaluateRightUnary(const std::string &value, IExceptionManager *exception, INode *expr) override;

			virtual Ptr evaluateBinary(const std::string &value, Ptr right, IStorage *storage, IExceptionManager *exception, INode *expr) override;

			virtual int rank() override;

			static const int CHAR_RANK		= 0x0000;
			static const int UCHAR_RANK		= 0x0001;
			static const int SHORT_RANK		= 0x0002;
			static const int USHORT_RANK	= 0x0003;
			static const int INT_RANK		= 0x0004;
			static const int UINT_RANK		= 0x0005;
			static const int LONG_RANK		= 0x0006;
			static const int ULONG_RANK		= 0x0007;
			static const int LLONG_RANK		= 0x0008;
			static const int ULLONG_RANK	= 0x0009;
			static const int FLOAT_RANK		= 0x000A;
			static const int DOUBLE_RANK	= 0x000B;
			static const int LDOUBLE_RANK	= 0x000C;
			static const int STRING_RANK	= 0x000D;
			static const int NAN_RANK		= 0xFFFF;

		protected:
			virtual Ptr promote_(Primitive *target);

			virtual Ptr evaluate_(const std::string &value, bool reversed, Ptr right, IExceptionManager *exception, INode *expr);

			virtual Ptr evaluateBinary_(const std::string &value, Ptr right, IStorage *storage, IExceptionManager *exception, INode *expr);

			virtual Ptr prepForExpression_();

			IType::Ptr type_;
			IMemory *memory_ = nullptr;
		};
	}
}

#endif /* !STRUCTURED_SCRIPT_PRIMITIVE_OBJECT_H */