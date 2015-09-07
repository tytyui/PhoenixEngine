#ifndef PHOENIX_GL_INTERFACE_H
#define PHOENIX_GL_INTERFACE_H

#include "ExternalLib/GLIncludes.h"
#include "Utility/Debug/Debug.h"
#include "Utility/Misc/Primitives.h"

namespace Phoenix
{
	namespace GL
	{
		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glClear.xml */
		namespace EClearBit
		{
			typedef GLbitfield Type;

			enum Mask : Type
			{
				Color = GL_COLOR_BUFFER_BIT,
				Depth = GL_DEPTH_BUFFER_BIT,
				Stencil = GL_STENCIL_BUFFER_BIT,
			};
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glGetError.xml */
		namespace EError
		{
			typedef GLenum Type;

			enum Value : Type
			{
				None = GL_NO_ERROR,
				InvalidEnum = GL_INVALID_ENUM,
				InvalidValue = GL_INVALID_VALUE,
				InvalidOperation = GL_INVALID_OPERATION,
				InvalidFrameBufferOperation = GL_INVALID_FRAMEBUFFER_OPERATION,
				OutOfMemory = GL_OUT_OF_MEMORY,
				StackUnderflow = GL_STACK_UNDERFLOW,
				StackOverflow = GL_STACK_OVERFLOW,
			};

			FChar* ToString(const EError::Type GLError)
			{
				switch (GLError)
				{
					case EError::None:
					{
						return "GL_NO_ERROR";
					}

					case EError::InvalidEnum:
					{
						return "GL_INVALID_ENUM";
					}

					case EError::InvalidValue:
					{
						return "GL_INVALID_VALUE";
					}

					case EError::InvalidOperation:
					{
						return "GL_INVALID_OPERATION";
					}

					case EError::InvalidFrameBufferOperation:
					{
						return "GL_INVALID_FRAMEBUFFER_OPERATION";
					}

					case EError::OutOfMemory:
					{
						return "GL_OUT_OF_MEMORY";
					}

					case EError::StackUnderflow:
					{
						return "GL_STACK_UNDERFLOW";
					}

					case EError::StackOverflow:
					{
						return "GL_STACK_OVERFLOW";
					}

					default:
					{
						F_Assert(false, "Invalid error ID.");
						break;
					}
				}

				F_Assert(false, "Invalid error handling.");
				return nullptr;
			}

			FChar* ToDescription(const EError::Type GLError)
			{
				switch (GLError)
				{
					case EError::None:
					{
						return "No error has been recorded.";
					}

					case EError::InvalidEnum:
					{
						return "An unacceptable value is specified for an enumerated argument.";
					}

					case EError::InvalidValue:
					{
						return "A numeric argument is out of range.";
					}

					case EError::InvalidOperation:
					{
						return "The specified operation is not allowed in the current state.";
					}

					case EError::InvalidFrameBufferOperation:
					{
						return "The framebuffer object is not complete.";
					}

					case EError::OutOfMemory:
					{
						return "There is not enough memory left to execute the command.";
					}

					case EError::StackUnderflow:
					{
						return "An attempt has been made to perform an operation that would cause an internal stack to underflow.";
					}

					case EError::StackOverflow:
					{
						return "An attempt has been made to perform an operation that would cause an internal stack to overflow.";
					}

					default:
					{
						F_Assert(false, "Invalid error ID.");
						break;
					}
				}

				F_Assert(false, "Invalid error handling.");
				return nullptr;
			}
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glCreateShader.xml */
		namespace EShader
		{
			typedef GLenum Type;

			enum Value : Type
			{
				Compute = GL_COMPUTE_SHADER,
				Vertex = GL_VERTEX_SHADER,
				TessControl = GL_TESS_CONTROL_SHADER,
				TessEvaluation = GL_TESS_EVALUATION_SHADER,
				Geometry = GL_GEOMETRY_SHADER,
				Fragment = GL_FRAGMENT_SHADER,
			};
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/html/glGetShader.xhtml */
		namespace EShaderData
		{
			typedef GLenum Type;

			enum Value : Type
			{
				ShaderType = GL_SHADER_TYPE,
				DeleteStatus = GL_DELETE_STATUS,
				CompileStatus = GL_COMPILE_STATUS,
				InfoLogLength = GL_INFO_LOG_LENGTH,
				SourceLength = GL_SHADER_SOURCE_LENGTH,
			};
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glAttachShader.xml */
		static inline void AttachShader(const GLuint Program, const GLuint Shader)
		{
			glAttachShader(Program, Shader);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glClear.xml */
		static inline void Clear(const EClearBit::Type ClearMask)
		{
			glClear(ClearMask);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glClearColor.xml */
		static inline void ClearColor(const GLclampf Red, const GLclampf Green, const GLclampf Blue, const GLclampf Alpha)
		{
			glClearColor(Red, Green, Blue, Alpha);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glCompileShader.xml */
		static inline void CompileShader(const GLuint Shader)
		{
			glCompileShader(Shader);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glCreateProgram.xml */
		static inline GLuint CreateProgram()
		{
			const GLuint Program = glCreateProgram();
			return Program;
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glCreateShader.xml */
		static inline GLuint CreateShader(const EShader::Value ShaderType)
		{
			const GLuint Shader = glCreateShader(ShaderType);
			return Shader;
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glDeleteProgram.xml */
		static inline void DeleteProgram(const GLuint Program)
		{
			glDeleteProgram(Program);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glDeleteShader.xml */
		static inline void DeleteShader(const GLuint Shader)
		{
			glDeleteShader(Shader);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glGetShaderInfoLog.xml */
		static inline void GetShaderInfoLog(const GLuint Shader, GLchar* InfoLog, GLsizei MaxLength, GLsizei& WrittenLength)
		{
			F_Assert(InfoLog, "InfoLog must not be null.");
			F_Assert(WrittenLength == 0, "This value must be initialized 0 by default.");
			glGetShaderInfoLog(Shader, MaxLength, &WrittenLength, InfoLog);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/html/glGetShader.xhtml */
		static inline void GetShaderiv(const GLuint Shader, EShaderData::Value ShaderData, GLint& OutResult)
		{
			F_Assert(OutResult == 0, "This value must be initialized to 0 by default.");
			glGetShaderiv(Shader, ShaderData, &OutResult);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glShaderSource.xml */
		static inline void ShaderSource(const GLuint Shader, const GLchar* Code)
		{
			const GLsizei Count = 1;
			const GLint* const Length = nullptr;
			glShaderSource(Shader, Count, &Code, Length);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glUseProgram.xml */
		static inline void UseProgram(const GLuint Program)
		{
			glUseProgram(Program);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glViewport.xml */
		static inline void Viewport(const GLint X, const GLint Y, const GLsizei Width, const GLsizei Height)
		{
			glViewport(X, Y, Width, Height);
		}
	}
}

// #FIXME: Move this to a config file when appropriate.
#define PHOENIX_DEBUG_GL 1

#ifndef PHOENIX_DEBUG_GL
#	define PHOENIX_DEBUG_GL 1
#endif

#if PHOENIX_DEBUG_GL

#	define F_GLDisplayErrors()													\
		for (;;) {																\
			const EError::Type GLError = glGetError();							\
																				\
			if (GLError == EError::None) {										\
				break;															\
			}																	\
																				\
			const FChar* const ErrorStr = EError::ToString(Error);				\
			const FChar* const Description = EError::ToDescription(Error);		\
																				\
			F_Assert(ErrorStr, "ErrorStr is null.");							\
			F_Assert(Description, "Description is null.");						\
			F_LogError("GL Error: " << ErrorStr << " - " << Description);		\
		}

#	define F_GLIgnoreErrors()													\
		for (;;) {																\
			const EError::Type GLError = glGetError();							\
																				\
			if (GLError == EError::None) {										\
				break;															\
			}																	\
		}

#	define F_GL(GLCall)			\
	(GLCall);					\
	F_GLDisplayErrors();

#else

#	define F_GLDisplayErrors()

#	define F_GLIgnoreErrors()

#	define F_GL(GLCall)			\
	(GLCall);

#endif

#endif
