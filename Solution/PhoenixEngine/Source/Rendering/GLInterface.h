#ifndef PHOENIX_GL_INTERFACE_H
#define PHOENIX_GL_INTERFACE_H

#include "ExternalLib/GLIncludes.h"
#include "Utility/Debug/Debug.h"
#include "Utility/Misc/Primitives.h"

namespace Phoenix
{
	namespace GL
	{
		namespace EBool
		{
			typedef GLenum Type;

			enum Value : Type
			{
				False = GL_FALSE,
				True = GL_TRUE
			};
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glBindBuffer.xml */
		namespace EBuffer
		{
			typedef GLenum Type;

			enum Value : Type
			{
				Array = GL_ARRAY_BUFFER,
				AtomicCounter = GL_ATOMIC_COUNTER_BUFFER,
				CopyRead = GL_COPY_READ_BUFFER,
				CopyWrite = GL_COPY_WRITE_BUFFER,
				DispatchIndirect = GL_DISPATCH_INDIRECT_BUFFER,

				DrawIndirect = GL_DRAW_INDIRECT_BUFFER,
				ElementArray = GL_ELEMENT_ARRAY_BUFFER,
				PixelPack = GL_PIXEL_PACK_BUFFER,
				PixelUnpack = GL_PIXEL_UNPACK_BUFFER,
				Query = GL_QUERY_BUFFER,

				ShaderStorage = GL_SHADER_STORAGE_BUFFER,
				Texture = GL_TEXTURE_BUFFER,
				TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
				Uniform = GL_UNIFORM_BUFFER
			};
		}

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

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glBufferData.xml */
		namespace EUsage
		{
			typedef GLenum Type;

			enum Value : Type
			{
				StreamDraw = GL_STREAM_DRAW,
				StreamRead = GL_STREAM_READ,
				StreamCopy = GL_STREAM_COPY,

				StaticDraw = GL_STATIC_DRAW,
				StaticRead = GL_STATIC_READ,
				StaticCopy = GL_STATIC_COPY,

				DynamicDraw = GL_DYNAMIC_DRAW,
				DynamicRead = GL_DYNAMIC_READ,
				DynamicCopy = GL_DYNAMIC_COPY
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

			static inline const FChar* const ToString(const EError::Type GLError)
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

			static inline const FChar* const ToDescription(const EError::Type GLError)
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

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glVertexAttribPointer.xml */
		namespace EType
		{
			typedef GLenum Type;

			enum Value
			{
				Byte = GL_BYTE,
				UByte = GL_UNSIGNED_BYTE,

				Short = GL_SHORT,
				UShort = GL_UNSIGNED_SHORT,

				Int = GL_INT,
				UInt = GL_UNSIGNED_INT,

				HalfFloat = GL_HALF_FLOAT,
				Float = GL_FLOAT,
				Double = GL_DOUBLE,

				Int2_10_10_10_Rev = GL_INT_2_10_10_10_REV,
				UInt2_10_10_10_Rev = GL_UNSIGNED_INT_2_10_10_10_REV,
				UInt10F_11F_11F_Rev = GL_UNSIGNED_INT_10F_11F_11F_REV,
			};
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glAttachShader.xml */
		static inline void AttachShader(const GLuint Program, const GLuint Shader)
		{
			glAttachShader(Program, Shader);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glBindBuffer.xml */
		static inline void BindBuffer(const EBuffer::Value Target, const GLuint Buffer)
		{
			glBindBuffer(Target, Buffer);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glBindVertexArray.xml */
		static inline void BindVertexArray(const GLuint Array)
		{
			glBindVertexArray(Array);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glBufferData.xml */
		static inline void BufferData(
			const EBuffer::Value Target, 
			const GLsizeiptr Size, 
			const GLvoid* Data, 
			const EUsage::Value Usage)
		{
			glBufferData(Target, Size, Data, Usage);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glBufferSubData.xml */
		static inline void BufferSubData(
			const EBuffer::Value Target, 
			const GLintptr Offset, 
			const GLsizeiptr Size, 
			const GLvoid* const Data)
		{
			glBufferSubData(Target, Offset, Size, Data);
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

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glDeleteBuffers.xml */
		static inline void DeleteBuffers(const GLsizei N, const GLuint* const Buffers)
		{
			glDeleteBuffers(N, Buffers);
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

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glDeleteVertexArrays.xml */
		static inline void DeleteVertexArrays(const GLsizei N, const GLuint* const Arrays)
		{
			glDeleteVertexArrays(N, Arrays);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glEnableVertexAttribArray.xml */
		static inline void EnableVertexAttribArray(const GLuint Index)
		{
			glEnableVertexAttribArray(Index);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glGenBuffers.xml */
		static inline void GenBuffers(const GLsizei BufferCount, GLuint* const Buffers)
		{
			glGenBuffers(BufferCount, Buffers);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glGenVertexArrays.xml */
		static inline void GenVertexArrays(const GLsizei N, GLuint* const Arrays)
		{
			glGenVertexArrays(N, Arrays);
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

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glVertexAttribPointer.xml */
		static inline void VertexAttribPointer(
			const GLuint Index,
			const GLint Size,
			const EType::Value Type,
			const EBool::Value Normalized,
			const GLsizei Stride,
			const GLvoid* const Pointer)
		{
			glVertexAttribPointer(Index, Size, Type, Normalized, Stride, Pointer);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glVertexAttribPointer.xml */
		static inline void VertexAttribIPointer(
			const GLuint Index,
			const GLint Size,
			const EType::Value Type,
			const GLsizei Stride,
			const GLvoid* const Pointer)
		{
			glVertexAttribIPointer(Index, Size, Type, Stride, Pointer);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glVertexAttribPointer.xml */
		static inline void VertexAttribLPointer(
			const GLuint Index,
			const GLint Size,
			const EType::Value Type,
			const GLsizei Stride,
			const GLvoid* const Pointer)
		{
			glVertexAttribLPointer(Index, Size, Type, Stride, Pointer);
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
#define PHOENIX_DEBUG_GL_MAX_ERROR_MSGS_PER_CALL 10

#ifndef PHOENIX_DEBUG_GL
#	if _DEBUG
#		define PHOENIX_DEBUG_GL 1
#	else
#		define PHOENIX_DEBUG_GL 0
#	endif
#endif

#if PHOENIX_DEBUG_GL

#	define F_GLDisplayErrors()														\
		for (UInt32 I = 0; I < PHOENIX_DEBUG_GL_MAX_ERROR_MSGS_PER_CALL; ++I)		\
		{																			\
			const GL::EError::Type GLError = glGetError();							\
																					\
			if (GLError == GL::EError::None)										\
			{																		\
				break;																\
			}																		\
																					\
			const FChar* const ErrorStr = GL::EError::ToString(GLError);			\
			const FChar* const Description = GL::EError::ToDescription(GLError);	\
																					\
			F_Assert(ErrorStr, "ErrorStr is null.");								\
			F_Assert(Description, "Description is null.");							\
			F_LogError("GL Error: " << ErrorStr << " - " << Description);			\
		}

#	define F_GLIgnoreErrors()													\
		for (UInt32 I = 0; I < PHOENIX_DEBUG_GL_MAX_ERROR_MSGS_PER_CALL; ++I)	\
		{																		\
			const GL::EError::Type GLError = glGetError();						\
																				\
			if (GLError == GL::EError::None)									\
			{																	\
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
