#pragma once

#ifndef STRUCTURED_SCRIPT_EXCEPTION_MANAGER_H
#define STRUCTURED_SCRIPT_EXCEPTION_MANAGER_H

#include "../Interfaces/IExceptionManager.h"

namespace StructuredScript{
	class ExceptionManager : public IExceptionManager{
	public:
		virtual ~ExceptionManager(){}

		virtual void clear() override;

		virtual void set(IAny::Ptr exception) override;

		virtual void setOnce() override;

		virtual void setExit(IAny::Ptr value) override;

		virtual void setReturn(IAny::Ptr value) override;

		virtual void setBreak() override;

		virtual void setContinue() override;

		virtual IAny::Ptr get() const override;

		virtual bool has() const override;

		virtual bool hasOnce() const override;

		virtual bool hasExit() const override;

		virtual bool hasReturn() const override;

		virtual bool hasBreak() const override;

		virtual bool hasContinue() const override;

		static const unsigned short NONE		= 0x0000;
		static const unsigned short ONCE		= 0x0001;
		static const unsigned short EXIT		= 0x0002;
		static const unsigned short RETURN		= 0x0003;
		static const unsigned short BREAK		= 0x0004;
		static const unsigned short CONTINUE	= 0x0005;

	private:
		IAny::Ptr exception_;
		unsigned short code_ = NONE;
	};
}

#endif /* !STRUCTURED_SCRIPT_EXCEPTION_MANAGER_H */