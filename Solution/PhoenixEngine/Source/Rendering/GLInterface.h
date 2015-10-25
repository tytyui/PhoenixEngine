#ifndef PHOENIX_GL_INTERFACE_H
#define PHOENIX_GL_INTERFACE_H

#include "ExternalLib/GLIncludes.h"
#include "Utility/Debug/Assert.h"
#include "Utility/Debug/Debug.h"
#include "Utility/Misc/Primitives.h"

namespace Phoenix
{
	namespace GL
	{
		typedef GLuint ElementBufferT;
		typedef GLuint ImageIDT;
		typedef GLsizei IndexCountT;
		typedef GLint MipmapLevelT;
		typedef GLuint VertexArrayT;
		typedef GLuint VertexBufferT;

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

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glEnable.xml */
		namespace ECapability
		{
			typedef GLenum Type;

			enum Value : Type
			{
				Blend = GL_BLEND,
				ClipDistance0 = GL_CLIP_DISTANCE0,
				ClipDistance1 = GL_CLIP_DISTANCE1,
				ClipDistance2 = GL_CLIP_DISTANCE2,
				ClipDistance3 = GL_CLIP_DISTANCE3,

				ClipDistance4 = GL_CLIP_DISTANCE4,
				ClipDistance5 = GL_CLIP_DISTANCE5,
				ColorLogicOp = GL_COLOR_LOGIC_OP,
				CullFace = GL_CULL_FACE,
				DebugOutput = GL_DEBUG_OUTPUT,

				DebugOutputSynchronous = GL_DEBUG_OUTPUT_SYNCHRONOUS,
				DepthClamp = GL_DEPTH_CLAMP,
				DepthTest = GL_DEPTH_TEST,
				Dither = GL_DITHER,
				FramebufferSRGB = GL_FRAMEBUFFER_SRGB,

				LineSmooth = GL_LINE_SMOOTH,
				MultiSample = GL_MULTISAMPLE,
				PolygonOffsetFill = GL_POLYGON_OFFSET_FILL,
				PolygonOffsetLine = GL_POLYGON_OFFSET_LINE,
				PolygonOffsetPoint = GL_POLYGON_OFFSET_POINT,

				PolygonSmooth = GL_POLYGON_SMOOTH,
				PrimitiveRestart = GL_PRIMITIVE_RESTART,
				PrimitiveRestartFixedIndex = GL_PRIMITIVE_RESTART_FIXED_INDEX,
				RasterizerDiscard = GL_RASTERIZER_DISCARD,
				SampleAlphaToCoverage = GL_SAMPLE_ALPHA_TO_COVERAGE,

				SampleAlphaToOne = GL_SAMPLE_ALPHA_TO_ONE,
				SampleCoverage = GL_SAMPLE_COVERAGE,
				SampleShading = GL_SAMPLE_SHADING,
				SampleMask = GL_SAMPLE_MASK,
				ScissorTest = GL_SCISSOR_TEST,

				StencilTest = GL_STENCIL_TEST,
				TextureCubeMapSeamless = GL_TEXTURE_CUBE_MAP_SEAMLESS,
				ProgramPointSize = GL_PROGRAM_POINT_SIZE
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

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glGetProgram.xml */
		namespace EGetProgram
		{
			typedef GLenum Type;

			enum Value : Type
			{
				DeleteStatus = GL_DELETE_STATUS,
				LinkStatus = GL_LINK_STATUS,
				ValidateStatus = GL_VALIDATE_STATUS,
				InfoLogLength = GL_INFO_LOG_LENGTH,
				AttachedShaders = GL_ATTACHED_SHADERS,

				ActiveAttributes = GL_ACTIVE_ATTRIBUTES,
				ActiveAttributeMaxLength = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
				ActiveUniforms = GL_ACTIVE_UNIFORMS,
				ActiveUniformMaxLength = GL_ACTIVE_UNIFORM_MAX_LENGTH
			};
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glDrawElements.xml */
		namespace EMode
		{
			typedef GLenum Type;

			enum Value : Type
			{
				Points = GL_POINTS,
				LineStrip = GL_LINE_STRIP,
				LineLoop = GL_LINE_LOOP,
				Lines = GL_LINES,
				LineStripAdjacency = GL_LINE_STRIP_ADJACENCY,

				LinesAdjacency = GL_LINES_ADJACENCY,
				TriangleStrip = GL_TRIANGLE_STRIP,
				TriangleFan = GL_TRIANGLE_FAN,
				Triangles = GL_TRIANGLES,
				TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY,

				TrianglesAdjacency = GL_TRIANGLES_ADJACENCY,
				Patches = GL_PATCHES
			};
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

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glGetShader.xml */
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

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glActiveTexture.xml */
		namespace ETex
		{
			typedef GLenum Type;

			enum Value : Type
			{
				T0 = GL_TEXTURE0,
				T1 = GL_TEXTURE1,
				T2 = GL_TEXTURE2,
				T3 = GL_TEXTURE3,
				T4 = GL_TEXTURE4,

				T5 = GL_TEXTURE5,
				T6 = GL_TEXTURE6,
				T7 = GL_TEXTURE7,
				T8 = GL_TEXTURE8,
				T9 = GL_TEXTURE9,

				T10 = GL_TEXTURE10,
				T11 = GL_TEXTURE11,
				T12 = GL_TEXTURE12,
				T13 = GL_TEXTURE13,
				T14 = GL_TEXTURE14,

				T15 = GL_TEXTURE15,
				T16 = GL_TEXTURE16,
				T17 = GL_TEXTURE17,
				T18 = GL_TEXTURE18,
				T19 = GL_TEXTURE19,

				T20 = GL_TEXTURE20,
				T21 = GL_TEXTURE21,
				T22 = GL_TEXTURE22,
				T23 = GL_TEXTURE23,
				T24 = GL_TEXTURE24,

				T25 = GL_TEXTURE25,
				T26 = GL_TEXTURE26,
				T27 = GL_TEXTURE27,
				T28 = GL_TEXTURE28,
				T29 = GL_TEXTURE29,

				T30 = GL_TEXTURE30,
				T31 = GL_TEXTURE31,
			};
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glTexImage2D.xml */
		namespace ETexFormat
		{
			typedef GLenum Type;

			enum Value : Type
			{
				Red = GL_RED,
				RG = GL_RG,
				RGB = GL_RGB,
				BGR = GL_BGR,
				RGBA = GL_RGBA,

				BGRA = GL_BGRA,
				RedInteger = GL_RED_INTEGER,
				RGInteger = GL_RG_INTEGER,
				RGBInteger = GL_RGB_INTEGER,
				BGRInteger = GL_BGR_INTEGER,

				RGBAInteger = GL_RGBA_INTEGER,
				BGRAInteger = GL_BGRA_INTEGER,
				StencilIndex = GL_STENCIL_INDEX,
				DepthComponent = GL_DEPTH_COMPONENT,
				DepthStencil = GL_DEPTH_STENCIL
			};
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glTexImage2D.xml
		Note: Only Table 1 (Base Internal Formats) are represented here. */
		namespace ETexGLFormat
		{
			typedef GLenum Type;

			enum Value : Type
			{
				DepthComponent = GL_DEPTH_COMPONENT,
				DepthStencil = GL_DEPTH_STENCIL,
				Red = GL_RED,
				RG = GL_RG,
				RGB = GL_RGB,
				RGBA = GL_RGBA,
			};
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glTexParameter.xml */
		namespace ETexMagFilter
		{
			typedef GLint Type;

			enum Value : Type
			{
				Nearest = GL_NEAREST,
				Linear = GL_LINEAR,
			};
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glTexParameter.xml */
		namespace ETexMinFilter
		{
			typedef GLint Type;

			enum Value : Type
			{
				Nearest = GL_NEAREST,
				Linear = GL_LINEAR,
				NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
				LinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,
				NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,
				LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR,
			};
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glTexParameter.xml */
		namespace ETexParameter
		{
			typedef GLenum Type;

			enum Value : Type
			{
				DepthStencilTextureMode = GL_DEPTH_STENCIL_TEXTURE_MODE,
				TextureBaseLevel = GL_TEXTURE_BASE_LEVEL,
				TextureCompareFunc = GL_TEXTURE_COMPARE_FUNC,
				TextureCompareMode = GL_TEXTURE_COMPARE_MODE,
				TextureLODBias = GL_TEXTURE_LOD_BIAS,

				TextureMinFilter = GL_TEXTURE_MIN_FILTER,
				TextureMagFilter = GL_TEXTURE_MAG_FILTER,
				TextureMinLOD = GL_TEXTURE_MIN_LOD,
				TextureMaxLOD = GL_TEXTURE_MAX_LOD,
				TextureMaxLevel = GL_TEXTURE_MAX_LEVEL,

				TextureSwizzleR = GL_TEXTURE_SWIZZLE_R,
				TextureSwizzleG = GL_TEXTURE_SWIZZLE_G,
				TextureSwizzleA = GL_TEXTURE_SWIZZLE_A,
				TextureWrapS = GL_TEXTURE_WRAP_S,
				TextureWrapT = GL_TEXTURE_WRAP_T,

				TextureWrapR = GL_TEXTURE_WRAP_R
			};
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glBindTexture.xml */
		namespace ETexTarget
		{
			typedef GLenum Type;

			enum Value : Type
			{
				T1D = GL_TEXTURE_1D,
				T2D = GL_TEXTURE_2D,
				T3D = GL_TEXTURE_3D,
				Array1D = GL_TEXTURE_1D_ARRAY,
				Array2D = GL_TEXTURE_2D_ARRAY,

				Rectangle = GL_TEXTURE_RECTANGLE,
				CubeMap = GL_TEXTURE_CUBE_MAP,
				CubeMapArray = GL_TEXTURE_CUBE_MAP_ARRAY,
				Buffer = GL_TEXTURE_BUFFER,
				MultiSample2D = GL_TEXTURE_2D_MULTISAMPLE,

				MultiSampleArray2D = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
			};
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glTexParameter.xml */
		namespace ETexWrap
		{
			typedef GLint Type;

			enum Value : Type
			{
				ClampToEdge = GL_CLAMP_TO_EDGE,
				ClampToBorder = GL_CLAMP_TO_BORDER,
				MirroredRepeat = GL_MIRRORED_REPEAT,
				Repeat = GL_REPEAT,
				MirrorClampToEdge = GL_MIRROR_CLAMP_TO_EDGE
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

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glActiveTexture.xml */
		static inline void ActiveTexture(const ETex::Value Texture)
		{
			glActiveTexture(Texture);
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

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glBindTexture.xml */
		static inline void BindTexture(const ETexTarget::Value Target, const GLuint Texture)
		{
			glBindTexture(Target, Texture);
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

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glDeleteTextures.xml */
		static inline void DeleteTextures(const GLsizei N, const GLuint* const Textures)
		{
			glDeleteTextures(N, Textures);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glDeleteVertexArrays.xml */
		static inline void DeleteVertexArrays(const GLsizei N, const GLuint* const Arrays)
		{
			glDeleteVertexArrays(N, Arrays);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glEnable.xml */
		static inline void Disable(const ECapability::Value Cap)
		{
			glDisable(Cap);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glDrawArrays.xml */
		static inline void DrawArrays(
			const EMode::Value Mode,
			const GLint First,
			const GLsizei Count)
		{
			glDrawArrays(Mode, First, Count);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glDrawElements.xml */
		static inline void DrawElements(
			const EMode::Value Mode,
			const GLsizei Count,
			const EType::Value Type,
			const GLvoid* const Indices)
		{
			glDrawElements(Mode, Count, Type, Indices);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glEnable.xml */
		static inline void Enable(const ECapability::Value Cap)
		{
			glEnable(Cap);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glEnableVertexAttribArray.xml */
		static inline void EnableVertexAttribArray(const GLuint Index)
		{
			glEnableVertexAttribArray(Index);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glGenerateMipmap.xml */
		static inline void GenerateMipmap(const ETexTarget::Value Target)
		{
			glGenerateMipmap(Target);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glGenTextures.xml */
		static inline void GenTextures(const GLsizei N, GLuint* const Textures)
		{
			glGenTextures(N, Textures);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glGetProgramInfoLog.xml */
		static inline void GetProgramInfoLog(
			const GLuint Program,
			const GLsizei MaxLength,
			GLsizei* const Length,
			GLchar* const InfoLog)
		{
			glGetProgramInfoLog(Program, MaxLength, Length, InfoLog);
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

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glGetProgram.xml */
		static inline void GetProgramiv(const GLuint Program, const EGetProgram::Value PName, GLint& Params)
		{
			glGetProgramiv(Program, PName, &Params);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glGetShaderInfoLog.xml */
		static inline void GetShaderInfoLog(
			const GLuint Shader,
			GLchar* const InfoLog,
			const GLsizei MaxLength,
			GLsizei& WrittenLength)
		{
			F_Assert(InfoLog, "InfoLog must not be null.");
			F_Assert(WrittenLength == 0, "This value must be initialized 0 by default.");

			glGetShaderInfoLog(Shader, MaxLength, &WrittenLength, InfoLog);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glGetShader.xml */
		static inline void GetShaderiv(const GLuint Shader, const EShaderData::Value ShaderData, GLint& OutResult)
		{
			F_Assert(OutResult == 0, "This value must be initialized to 0 by default.");
			glGetShaderiv(Shader, ShaderData, &OutResult);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glGetUniformLocation.xml */
		static inline GLint GetUniformLocation(const GLuint Program, const GLchar* const Name)
		{
			const GLint UniformLocation = glGetUniformLocation(Program, Name);
			return UniformLocation;
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glLinkProgram.xml */
		static inline void LinkProgram(const GLuint Program)
		{
			glLinkProgram(Program);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glShaderSource.xml */
		static inline void ShaderSource(const GLuint Shader, const GLchar* Code)
		{
			const GLsizei Count = 1;
			const GLint* const Length = nullptr;
			glShaderSource(Shader, Count, &Code, Length);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glTexImage2D.xml */
		static inline void TexImage2D(
			const ETexTarget::Value Target,
			const GLint Level,
			const GLint InternalFormat,
			const GLsizei Width,
			const GLsizei Height,
			const ETexFormat::Value Format,
			const EType::Value Type,
			const GLvoid* const Data)
		{
			glTexImage2D(Target, Level, InternalFormat, Width, Height, 0, Format, Type, Data);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glTexParameter.xml */
		static inline void TexParameterf(
			const ETexTarget::Value Target,
			const ETexParameter::Value PName,
			const GLfloat Param)
		{
			glTexParameterf(Target, PName, Param);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glTexParameter.xml */
		static inline void TexParameteri(
			const ETexTarget::Value Target,
			const ETexParameter::Value PName,
			const GLint Param)
		{
			glTexParameteri(Target, PName, Param);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glUniform.xml */
		static inline void Uniform1f(const GLint Location, const GLfloat V0)
		{
			glUniform1f(Location, V0);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glUniform.xml */
		static inline void Uniform2f(const GLint Location, const GLfloat V0, const GLfloat V1)
		{
			glUniform2f(Location, V0, V1);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glUniform.xml */
		static inline void Uniform3f(
			const GLint Location,
			const GLfloat V0,
			const GLfloat V1,
			const GLfloat V2)
		{
			glUniform3f(Location, V0, V1, V2);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glUniform.xml */
		static inline void Uniform4f(
			const GLint Location,
			const GLfloat V0,
			const GLfloat V1,
			const GLfloat V2,
			const GLfloat V3)
		{
			glUniform4f(Location, V0, V1, V2, V3);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glUniform.xml */
		static inline void Uniform1i(const GLint Location, const GLint V0)
		{
			glUniform1i(Location, V0);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glUniform.xml */
		static inline void Uniform2i(const GLint Location, const GLint V0, const GLint V1)
		{
			glUniform2i(Location, V0, V1);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glUniform.xml */
		static inline void Uniform3i(
			const GLint Location,
			const GLint V0,
			const GLint V1,
			const GLint V2)
		{
			glUniform3i(Location, V0, V1, V2);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glUniform.xml */
		static inline void Uniform4i(
			const GLint Location,
			const GLint V0,
			const GLint V1,
			const GLint V2,
			const GLint V3)
		{
			glUniform4i(Location, V0, V1, V2, V3);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glUniform.xml */
		static inline void Uniform1fv(
			const GLint Location,
			const GLsizei Count,
			const GLfloat* const Value)
		{
			glUniform1fv(Location, Count, Value);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glUniform.xml */
		static inline void Uniform2fv(
			const GLint Location,
			const GLsizei Count,
			const GLfloat* const Value)
		{
			glUniform2fv(Location, Count, Value);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glUniform.xml */
		static inline void Uniform3fv(
			const GLint Location,
			const GLsizei Count,
			const GLfloat* const Value)
		{
			glUniform3fv(Location, Count, Value);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glUniform.xml */
		static inline void Uniform4fv(
			const GLint Location,
			const GLsizei Count,
			const GLfloat* const Value)
		{
			glUniform4fv(Location, Count, Value);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glUniform.xml */
		static inline void Uniform1iv(
			const GLint Location,
			const GLsizei Count,
			const GLint* const Value)
		{
			glUniform1iv(Location, Count, Value);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glUniform.xml */
		static inline void Uniform2iv(
			const GLint Location,
			const GLsizei Count,
			const GLint* const Value)
		{
			glUniform2iv(Location, Count, Value);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glUniform.xml */
		static inline void Uniform3iv(
			const GLint Location,
			const GLsizei Count,
			const GLint* const Value)
		{
			glUniform3iv(Location, Count, Value);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glUniform.xml */
		static inline void Uniform4iv(
			const GLint Location,
			const GLsizei Count,
			const GLint* const Value)
		{
			glUniform4iv(Location, Count, Value);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glUniform.xml */
		static inline void Uniform1uiv(
			const GLint Location,
			const GLsizei Count,
			const GLuint* const Value)
		{
			glUniform1uiv(Location, Count, Value);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glUniform.xml */
		static inline void Uniform2uiv(
			const GLint Location,
			const GLsizei Count,
			const GLuint* const Value)
		{
			glUniform2uiv(Location, Count, Value);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glUniform.xml */
		static inline void Uniform3uiv(
			const GLint Location,
			const GLsizei Count,
			const GLuint* const Value)
		{
			glUniform3uiv(Location, Count, Value);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glUniform.xml */
		static inline void Uniform4uiv(
			const GLint Location,
			const GLsizei Count,
			const GLuint* const Value)
		{
			glUniform4uiv(Location, Count, Value);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glUniform.xml */
		static inline void UniformMatrix2fv(
			const GLint Location,
			const GLsizei Count,
			const GLboolean Transpose,
			const GLfloat* const Value)
		{
			glUniformMatrix2fv(Location, Count, Transpose, Value);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glUniform.xml */
		static inline void UniformMatrix3fv(
			const GLint Location,
			const GLsizei Count,
			const GLboolean Transpose,
			const GLfloat* const Value)
		{
			glUniformMatrix3fv(Location, Count, Transpose, Value);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glUniform.xml */
		static inline void UniformMatrix4fv(
			const GLint Location,
			const GLsizei Count,
			const GLboolean Transpose,
			const GLfloat* const Value)
		{
			glUniformMatrix4fv(Location, Count, Transpose, Value);
		}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glUseProgram.xml */
		static inline void UseProgram(const GLuint Program)
		{
			glUseProgram(Program);
	}

		/* Ref: https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glValidateProgram.xml */
		static inline void ValidateProgram(const GLuint Program)
		{
			glValidateProgram(Program);
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
		for (UInt32 I = 0; I < PHOENIX_DEBUG_GL_MAX_ERROR_MSGS_PER_CALL; ++I)			\
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
		for (UInt32 I = 0; I < PHOENIX_DEBUG_GL_MAX_ERROR_MSGS_PER_CALL; ++I)		\
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
