/******************************************************************************
 * Spine Runtimes Software License v2.5
 *
 * Copyright (c) 2013-2016, Esoteric Software
 * All rights reserved.
 *
 * You are granted a perpetual, non-exclusive, non-sublicensable, and
 * non-transferable license to use, install, execute, and perform the Spine
 * Runtimes software and derivative works solely for personal or internal
 * use. Without the written permission of Esoteric Software (see Section 2 of
 * the Spine Software License Agreement), you may not (a) modify, translate,
 * adapt, or develop new applications using the Spine Runtimes or otherwise
 * create derivative works or improvements of the Spine Runtimes or (b) remove,
 * delete, alter, or obscure any trademarks or any copyright, trademark, patent,
 * or other intellectual property or proprietary rights notices on or in the
 * Software, including any copy thereof. Redistributions in binary or source
 * form must include this license and terms.
 *
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, BUSINESS INTERRUPTION, OR LOSS OF
 * USE, DATA, OR PROFITS) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#pragma once

#include "Components/ActorComponent.h"
#include "ProceduralMeshComponent.h"
#include "SpineSkeletonAnimationComponent.h"
#include "SpineSkeletonRendererComponent.generated.h"


UCLASS(ClassGroup=(Spine), meta=(BlueprintSpawnableComponent))
class SPINEPLUGIN_API USpineSkeletonRendererComponent: public UProceduralMeshComponent {
	GENERATED_BODY()

public: 
	USpineSkeletonRendererComponent (const FObjectInitializer& ObjectInitializer);
	
	virtual void BeginPlay () override;
		
	virtual void TickComponent (float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/* Updates this skeleton renderer using the provided skeleton animation component. */
	void UpdateRenderer(USpineSkeletonComponent* Skeleton);

	// Material Instance parents
	UPROPERTY(Category = Spine, EditAnywhere, BlueprintReadOnly)
	UMaterialInterface* NormalBlendMaterial;
	
	UPROPERTY(Category = Spine, EditAnywhere, BlueprintReadOnly)
	UMaterialInterface* AdditiveBlendMaterial;
	
	UPROPERTY(Category = Spine, EditAnywhere, BlueprintReadOnly)
	UMaterialInterface* MultiplyBlendMaterial;
	
	UPROPERTY(Category = Spine, EditAnywhere, BlueprintReadOnly)
	UMaterialInterface* ScreenBlendMaterial;

	// Need to hold on to the dynamic instances, or the GC will kill us while updating them
	UPROPERTY(Category = Spine, EditAnywhere, BlueprintReadWrite)
	TArray<UMaterialInstanceDynamic*> atlasNormalBlendMaterials;
	TMap<spine::AtlasPage*, UMaterialInstanceDynamic*> pageToNormalBlendMaterial;
	
	UPROPERTY(Category = Spine, EditAnywhere, BlueprintReadWrite)
	TArray<UMaterialInstanceDynamic*> atlasAdditiveBlendMaterials;
	TMap<spine::AtlasPage*, UMaterialInstanceDynamic*> pageToAdditiveBlendMaterial;
	
	UPROPERTY(Category = Spine, EditAnywhere, BlueprintReadWrite)
	TArray<UMaterialInstanceDynamic*> atlasMultiplyBlendMaterials;
	TMap<spine::AtlasPage*, UMaterialInstanceDynamic*> pageToMultiplyBlendMaterial;
	
	UPROPERTY(Category = Spine, EditAnywhere, BlueprintReadWrite)
	TArray<UMaterialInstanceDynamic*> atlasScreenBlendMaterials;
	TMap<spine::AtlasPage*, UMaterialInstanceDynamic*> pageToScreenBlendMaterial;
	
	UPROPERTY(Category = Spine, EditAnywhere, BlueprintReadWrite)
	float DepthOffset = 0.1f;
	
	UPROPERTY(Category = Spine, EditAnywhere, BlueprintReadWrite)
	FName TextureParameterName;

	UPROPERTY(Category = Spine, EditAnywhere, BlueprintReadWrite)
	FLinearColor Color = FLinearColor(1, 1, 1, 1);

	/** Whether to generate collision geometry for the skeleton, or not. */
	UPROPERTY(Category = Spine, EditAnywhere, BlueprintReadWrite)
	bool bCreateCollision;

	virtual void FinishDestroy() override;
	
protected:
	void UpdateMesh (spine::Skeleton* Skeleton);

	void Flush (int &Idx, TArray<FVector> &Vertices, TArray<int32> &Indices, TArray<FVector2D> &Uvs, TArray<FColor> &Colors, TArray<FVector> &Colors2, UMaterialInstanceDynamic* Material);
	
	spine::Vector<float> worldVertices;
	spine::SkeletonClipping clipper;
};