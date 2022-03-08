// Shoot Them Up Game

using UnrealBuildTool;

public class ShootThemUp : ModuleRules
{
	public ShootThemUp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
		{
		 "Core",
		 "CoreUObject",
		 "Engine",
		 "InputCore",
		 "Niagara",
		 "PhysicsCore",
		 "GameplayTasks",
		 "NavigationSystem"
		 
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[]
		{
			"ShootThemUp/Public/Player",
			"ShootThemUp/Public/Components",
			"ShootThemUp/Public/Dev",
			"ShootThemUp/Public/Weapon",
			"ShootThemUp/Public/UI",
			"ShootThemUp/Public/Animations",
			"ShootThemUp/Public/Pickups",
			"ShootThemUp/Public/Weapon/Components",
			"ShootThemUp/Public/AI",
			"ShootThemUp/Public/AI/Tasks",
			"ShootThemUp/Public/AI/Services",
			"ShootThemUp/Public/AI/EQS",
			"ShootThemUp/Public/AI/Decorates",
			"ShootThemUp/Public/Menu",
			"ShootThemUp/Public/Menu/UI",
			"ShootThemUp/Public/Sound"
		});
	}
}