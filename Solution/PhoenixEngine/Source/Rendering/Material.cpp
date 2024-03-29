#include "Rendering/Material.h"

#include "Utility/Debug/Assert.h"
#include "Math/Math.h"

using namespace Phoenix;

bool EMaterialType::IsValid(const EMaterialType::Type MaterialType)
{
	const bool IsEnumValid = MaterialType < EMaterialType::Count;
	return IsEnumValid;
}

FVector2D FMaterialBase::ColourRange = FVector2D(0.f, 1.f);

FMaterialBase FMaterialBase::Create(
	const EMaterialType::Value MaterialType,
	const FVector4D& Colour)
{
	F_Assert(EMaterialType::IsValid(MaterialType), "Material type is invalid.");
	for (glm::length_t I = 0; I < Colour.length(); ++I)
	{
		F_Assert(FMathf::IsInRange(Colour[I], 0.f, 1.f),
			"Invalid Colour value.");
	}

	FMaterialBase MaterialBase;

	MaterialBase.MaterialType = MaterialType;
	MaterialBase.Colour = Colour;

	return MaterialBase;
}

const FVector2D FAshikMaterial::AnisotropicRange = FVector2D(1.f, 10000.f);

FAshikMaterial FAshikMaterial::Create(
	const Float32 AnisotropicU,
	const Float32 AnisotropicV)
{
	F_Assert(FMathf::IsInRange(AnisotropicU, AnisotropicRange.x, AnisotropicRange.y),
		"Invalid AnisotropicU value.");
	F_Assert(FMathf::IsInRange(AnisotropicV, AnisotropicRange.x, AnisotropicRange.y),
		"Invalid AnisotropicV value.");

	FAshikMaterial Ashik;

	Ashik.AnisotropicU = AnisotropicU;
	Ashik.AnisotropicV = AnisotropicV;

	return Ashik;
}

const FVector2D FBlinnMaterial::SpecularExpRange = FVector2D(1.f, 1024.f);

FBlinnMaterial FBlinnMaterial::Create(
	const Float32 SpecularExp)
{
	F_Assert(FMathf::IsInRange(SpecularExp, SpecularExpRange.x, SpecularExpRange.y),
		"Invalid SpecularExp value.");

	FBlinnMaterial Blinn;

	Blinn.SpecularExp = SpecularExp;

	return Blinn;
}

const FVector2D FCookMaterial::RoughnessRange = FVector2D(0.00001f, 1.f);
const FVector2D FCookMaterial::RefANIRange = FVector2D(1.f, 5.f);

FCookMaterial FCookMaterial::Create(
	const Float32 Roughness,
	const Float32 RefANI)
{
	F_Assert(FMathf::IsInRange(Roughness, RoughnessRange.x, RoughnessRange.y),
		"Invalid Roughness value.");
	F_Assert(FMathf::IsInRange(RefANI, RefANIRange.x, RefANIRange.y),
		"Invalid RefANI value.");

	FCookMaterial Cook;

	Cook.Roughness = Roughness;
	Cook.RefANI = RefANI;

	return Cook;
}

const FVector2D FStraussMaterial::SmoothnessRange = FVector2D(0.f, 0.99999f);
const FVector2D FStraussMaterial::MetalnessRange = FVector2D(0.f, 1.f);
const FVector2D FStraussMaterial::TransparencyRange = FVector2D(0.f, 1.f);

FStraussMaterial FStraussMaterial::Create(
	const Float32 Smoothness,
	const Float32 Metalness,
	const Float32 Transparency)
{
	F_Assert(FMathf::IsInRange(Smoothness, SmoothnessRange.x, SmoothnessRange.y),
		"Invalid Smoothness value.");
	F_Assert(FMathf::IsInRange(Metalness, MetalnessRange.x, MetalnessRange.y),
		"Invalid Metalness value.");
	F_Assert(FMathf::IsInRange(Transparency, TransparencyRange.x, TransparencyRange.y),
		"Invalid Transparency value.");

	FStraussMaterial Strauss;

	Strauss.Smoothness = Smoothness;
	Strauss.Metalness = Metalness;
	Strauss.Transparency = Transparency;

	return Strauss;
}

const FVector2D FWardMaterial::RoughnessRange = FVector2D(0.f, 1.f);

FWardMaterial FWardMaterial::Create(
	const Float32 Roughness)
{
	F_Assert(FMathf::IsInRange(Roughness, RoughnessRange.x, RoughnessRange.y),
		"Invalid Transparency value.");

	FWardMaterial Ward;

	Ward.Roughness = Roughness;

	return Ward;
}

FMaterial FMaterial::CreateDefault(const FVector4D& Colour)
{
	const FMaterial Material = CreateBlinn(Colour, FBlinnMaterial::SpecularExpRange.x);
	return Material;
}

FMaterial FMaterial::CreateAshik(
	const FVector4D& Colour,
	const Float32 AnisotropicU,
	const Float32 AnisotropicV)
{
	FMaterial Material;

	Material.Base = FMaterialBase::Create(EMaterialType::Ashik, Colour);
	Material.Ashik = FAshikMaterial::Create(AnisotropicU, AnisotropicV);

	return Material;
}

FMaterial FMaterial::CreateBlinn(
	const FVector4D& Colour,
	const Float32 SpecularExp)
{
	FMaterial Material;

	Material.Base = FMaterialBase::Create(EMaterialType::Blinn, Colour);
	Material.Blinn = FBlinnMaterial::Create(SpecularExp);

	return Material;
}

FMaterial FMaterial::CreateCook(
	const FVector4D& Colour,
	const Float32 Roughness,
	const Float32 RefANI)
{
	FMaterial Material;

	Material.Base = FMaterialBase::Create(EMaterialType::Cook, Colour);
	Material.Cook = FCookMaterial::Create(Roughness, RefANI);

	return Material;
}

FMaterial FMaterial::CreateStrauss(
	const FVector4D& Colour,
	const Float32 Smoothness,
	const Float32 Metalness,
	const Float32 Transparency)
{
	FMaterial Material;

	Material.Base = FMaterialBase::Create(EMaterialType::Strauss, Colour);
	Material.Strauss = FStraussMaterial::Create(Smoothness, Metalness, Transparency);

	return Material;
}

FMaterial FMaterial::CreateWard(
	const FVector4D& Colour,
	const Float32 Roughness)
{
	FMaterial Material;

	Material.Base = FMaterialBase::Create(EMaterialType::Ward, Colour);
	Material.Ward = FWardMaterial::Create(Roughness);

	return Material;
}
