#pragma once

#include "meta_jni.hpp"
#include<string>
#include "maths/maths.hpp"

namespace maps
{
	BEGIN_KLASS_DEF(Object, "java/lang/Object")
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(Class, "java/lang/Class")
		operator jclass() const
		{
			return (jclass)object_instance;
		}
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(String, "java/lang/String")
		static String create(const char* str)
		{
			return String(jni::get_env()->NewStringUTF(str));
		}


		std::string to_string() const
		{
			if (!object_instance) return std::string();
			jstring str_obj = (jstring)object_instance;
			jsize utf8_size = jni::get_env()->GetStringUTFLength(str_obj);
			jsize size = jni::get_env()->GetStringLength(str_obj);

			std::string str(utf8_size, '\0');
			jni::get_env()->GetStringUTFRegion(str_obj, 0, size, str.data());
			return str;
		}
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(Collection, "java/util/Collection")
		jni::method<jni::array<Object>, "toArray"> toArray{ *this };
	END_KLASS_DEF()
	BEGIN_KLASS_DEF_EX(List, "java/util/List", Collection)
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(URL, "java/net/URL")
		jni::constructor<String> constructor{ *this };

		jni::method<String, "toString"> toString{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(ClassLoader, "java/lang/ClassLoader");
		jni::method<Class, "findClass", jni::NOT_STATIC, String> findClass{ *this };
	END_KLASS_DEF()
	BEGIN_KLASS_DEF_EX(URLClassLoader, "java/net/URLClassLoader", ClassLoader)
		jni::constructor<jni::array<URL>> constructor{ *this };
		jni::constructor<jni::array<URL>, ClassLoader> constructor2{ *this };

		jni::method<void, "addURL", jni::NOT_STATIC, URL> addURL{ *this };
		jni::method<jni::array<URL>, "getURLs", jni::NOT_STATIC> getURLs{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(Double, "java/lang/Double")
		jni::method<jdouble, "doubleValue"> doubleValue{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(PrintStream, "java/io/PrintStream")
		jni::method<void, "println", jni::NOT_STATIC, String> println{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(System, "java/lang/System")
		jni::field<PrintStream, "out", jni::STATIC> out{ *this };
	END_KLASS_DEF()




	BEGIN_KLASS_DEF(Vec3d, "net/minecraft/class_243")
		jni::field<jdouble, "field_1352"> x{ *this };
		jni::field<jdouble, "field_1351"> y{ *this };
		jni::field<jdouble, "field_1350"> z{ *this };

		maths::vector3d to_vector3d()
		{
			return { x.get(), y.get(), z.get() };
		}
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(Item, "net/minecraft/class_1792")
	END_KLASS_DEF()
	BEGIN_KLASS_DEF_EX(SwordItem, "net/minecraft/class_1829", Item)
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(Items, "net/minecraft/class_1802")
		jni::field<Item, "field_8288", jni::STATIC> TOTEM_OF_UNDYING{ *this };
		jni::field<Item, "field_8436", jni::STATIC> SPLASH_POTION{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(BlockPos, "net/minecraft/class_2338")
		jni::field<BlockPos, "field_10980", jni::STATIC> ORIGIN{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(Direction, "net/minecraft/class_2350")
		jni::field<Direction, "field_11033", jni::STATIC> DOWN{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(Packet, "net/minecraft/class_2596")
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(ClientPlayNetworkHandler, "net/minecraft/class_634")
		jni::method<void, "method_2883", jni::NOT_STATIC, Packet> sendPacket{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(PlayerActionC2SPacket$Action, "net/minecraft/class_2846$class_2847")
		jni::field<PlayerActionC2SPacket$Action, "field_12969", jni::STATIC> SWAP_ITEM_WITH_OFFHAND{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(PlayerActionC2SPacket, "net/minecraft/class_2846")
		jni::constructor<PlayerActionC2SPacket$Action, BlockPos, Direction> constructor{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(PickFromInventoryC2SPacket, "net/minecraft/class_2838")
		jni::constructor<jint> constructor{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(ClickSlotC2SPacket, "net/minecraft/class_2813")
		jni::constructor<jint> constructor{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(ScreenHandler, "net/minecraft/class_1703")
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(UpdateSelectedSlotC2SPacket, "net/minecraft/class_2868")
		jni::constructor<jint> constructor{ *this };
		jni::method<jint, "method_12442"> getSelectedSlot{ *this };
		jni::field<jint, "field_13052"> selectedSlot{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(NbtCompound, "net/minecraft/class_2487")
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(ItemStack, "net/minecraft/class_1799")
		jni::field<Item, "field_8038"> item{ *this };
		jni::method<jboolean, "method_7960"> isEmpty{ *this };
		jni::method<ItemStack, "method_7971", jni::NOT_STATIC, jint> split{ *this };
		jni::method<jboolean, "method_31574", jni::NOT_STATIC, Item> isOf{ *this };
		jni::method<jboolean, "method_7972", jni::NOT_STATIC> copy{ *this };
		jni::method<NbtCompound, "method_7969", jni::NOT_STATIC> getNbt{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(Potion, "net/minecraft/class_1842")
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(PotionUtil, "net/minecraft/class_1844")
		jni::method<Potion, "method_8057", jni::NOT_STATIC, NbtCompound> getPotion{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(Potions, "net/minecraft/class_1847")
		jni::field<Potion, "field_8963", jni::STATIC> HEALING{ *this };
		jni::field<Potion, "field_8980", jni::STATIC> STRONG_HEALING{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(PlayerInventory, "net/minecraft/class_1661")
		jni::method<jint, "method_7395", jni::NOT_STATIC, ItemStack> getSlotWithStack{ *this };
		jni::field<List, "field_7547"> main{ *this };
		jni::field<jint, "field_7545"> selectedSlot{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(Inventory, "net/minecraft/class_1263")
		jni::method<ItemStack, "method_5438", jni::NOT_STATIC, jint> getStack{ *this };
		jni::method<jint, "method_5439"> size{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(Box, "net/minecraft/class_238")
		jni::field<jdouble, "field_1323"> minX{ *this };
		jni::field<jdouble, "field_1322"> minY{ *this };
		jni::field<jdouble, "field_1321"> minZ{ *this };
		jni::field<jdouble, "field_1320"> maxX{ *this };
		jni::field<jdouble, "field_1325"> maxY{ *this };
		jni::field<jdouble, "field_1324"> maxZ{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(EntityPose, "net/minecraft/class_4050")
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(EntityDimensions, "net/minecraft/class_4048")
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(StatusEffect, "net/minecraft/class_1291")
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(StatusEffects, "net/minecraft/class_1294")
		jni::field<StatusEffect, "field_5912", jni::STATIC> GLOWING{ *this };
		jni::field<StatusEffect, "field_5925", jni::STATIC> NIGHT_VISION{ *this };
		jni::field<StatusEffect, "field_5918", jni::STATIC> FIRE_RESISTANCE{ *this };
		jni::field<StatusEffect, "field_5924", jni::STATIC> REGENERATION{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(StatusEffectInstance, "net/minecraft/class_1293")
		jni::constructor<StatusEffect, jint, jint> constructor{ *this };
	END_KLASS_DEF()
	
	BEGIN_KLASS_DEF(Text, "net/minecraft/class_2561")
		jni::method<String, "method_54160"> getLiteralString{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(Hand, "net/minecraft/class_1268")
		jni::field<Hand, "field_5808", jni::STATIC> MAIN_HAND{ *this };
		jni::field<Hand, "field_5810", jni::STATIC> OFF_HAND{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(Entity, "net/minecraft/class_1297")
		jni::field<jint, "field_6012"> age{ *this };
		jni::field<Vec3d, "field_22467"> pos{ *this };
		jni::field<jfloat, "field_6031"> yaw{ *this };
		jni::field<jfloat, "field_5965"> pitch{ *this };
		jni::field<jfloat, "field_5982"> prevYaw{ *this };
		jni::field<jfloat, "field_6004"> prevPitch{ *this };
		jni::field<Box, "field_6005"> boundingBox{ *this };
		jni::field<jfloat, "field_6017"> fallDistance{ *this };
		jni::field<jboolean, "field_5952"> onGround{ *this };

		jni::field<jdouble, "field_6038"> lastRenderX{ *this };
		jni::field<jdouble, "field_5971"> lastRenderY{ *this };
		jni::field<jdouble, "field_5989"> lastRenderZ{ *this };

		maths::vector3d get_prev_position()
		{
			return { lastRenderX.get(), lastRenderY.get(), lastRenderZ.get() };
		}

		maths::vector3d get_position()
		{
			return pos.get().to_vector3d();
		}

		maths::angles get_prev_angles()
		{
			return { prevYaw.get(), prevPitch.get() };
		}

		maths::angles get_angles()
		{
			return { yaw.get(), pitch.get() };
		}

		jni::method<EntityPose, "method_18376"> getPose{ *this };
		jni::method<EntityDimensions, "method_18377", jni::NOT_STATIC, EntityPose> getDimensions{ *this };
		jni::method<jfloat, "method_18381", jni::NOT_STATIC, EntityPose> getEyeHeight{ *this };
		jni::method<Text, "method_23315"> getDefaultName{ *this };
		jni::method<String, "method_5820"> getEntityName{ *this };
		jni::method<Text, "method_7306"> getNameAndUUID{ *this }; 
		jni::method<jboolean, "method_5805"> isAlive{ *this };

		jni::method<jboolean, "method_5624", jni::NOT_STATIC> isSprinting{ *this };
		jni::method<void, "method_5728", jni::NOT_STATIC, jboolean> setSprinting{ *this };
		jni::method<void, "method_5834", jni::NOT_STATIC, jboolean> setGlowing{ *this };
		jni::method<void, "method_5729", jni::NOT_STATIC, jint, jboolean> setFlag{ *this };

		jni::method<jboolean, "method_5681"> isSwimming{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF_EX(LivingEntity, "net/minecraft/class_1309", Entity)
		jni::field<jint, "field_6273"> lastAttackedTicks{ *this };
	    jni::field<jint, "field_6235"> hurtTime{ *this };
	    jni::field<jint, "field_6228"> jumpingCooldown{ *this };

		jni::method<jboolean, "method_6128"> isFallFlying{ *this };
		jni::method<jboolean, "method_6113"> isSleeping{ *this };
		jni::method<jboolean, "method_6115"> isUsingItem{ *this };

		jni::method<void, "method_6043"> jump{ *this };
		jni::method<jboolean, "method_24518", jni::NOT_STATIC, Item> isHolding{ *this };
		jni::method<ItemStack, "method_6047"> getMainHandStack{ *this };
		jni::method<jboolean, "method_6092", jni::NOT_STATIC, StatusEffectInstance> addStatusEffect{ *this };
		jni::method<jboolean, "method_6016", jni::NOT_STATIC, StatusEffect> removeStatusEffect{ *this };
		jni::method<jboolean, "method_6092", jni::NOT_STATIC, jint> hasStatusEffect{ *this };
		jni::method<void, "method_6122", jni::NOT_STATIC, Hand, ItemStack> setStackInHand{ *this };

		jni::method<void, "method_6104", jni::NOT_STATIC, Hand> swingHand{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF_EX(PlayerEntity, "net/minecraft/class_1657", LivingEntity)
		jni::method<jfloat, "method_7261", jni::NOT_STATIC, jfloat> getAttackCooldownProgress{ *this };
		jni::method<ItemStack, "method_6079", jni::NOT_STATIC> getOffHandStack{ *this };
		jni::method<PlayerInventory, "method_31548"> getInventory{ *this };
		jni::field<ScreenHandler, "field_7512"> currentScreenHandler{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF_EX(AbstractClientPlayerEntity, "net/minecraft/class_742", PlayerEntity)
	END_KLASS_DEF()

	BEGIN_KLASS_DEF_EX(ClientPlayerEntity, "net/minecraft/class_746", AbstractClientPlayerEntity)
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(ClientWorld, "net/minecraft/class_638")
		jni::field<List, "field_18226"> players{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(SimpleOption, "net/minecraft/class_7172")
		jni::field<Object, "field_37868"> value{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(KeyBinding, "net/minecraft/class_304")
		jni::method<jboolean, "method_1434"> isPressed{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(GameOptions, "net/minecraft/class_315")
		jni::field<SimpleOption, "field_1843"> mouseSensitivity{ *this };
		jni::field<jdouble, "field_1840"> gammaSetting{ *this };
		jni::field<KeyBinding, "field_1886"> attackKey{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(Mouse, "net/minecraft/class_312")
		jni::field<jdouble, "field_1789"> cursorDeltaX{ *this };
		jni::field<jdouble, "field_1787"> cursorDeltaY{ *this };

		jni::method<void, "method_1606"> updateMouse{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(RenderTickCounter, "net/minecraft/class_317")
		jni::field<jfloat, "field_1970"> tickDelta{ *this };
	END_KLASS_DEF()
		
	BEGIN_KLASS_DEF(HitResult$Type, "net/minecraft/class_239$class_240")
		jni::field<HitResult$Type, "field_1331", jni::STATIC> ENTITY{ *this };
		jni::field<HitResult$Type, "field_1332", jni::STATIC> BLOCK{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(HitResult, "net/minecraft/class_239")
		jni::method<HitResult$Type, "method_17783"> getType{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF_EX(EntityHitResult, "net/minecraft/class_3966", HitResult)
		jni::field<Entity, "field_17592"> entity{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(ClientPlayerInteractionManager, "net/minecraft/class_636")
		jni::method<void, "method_2918", jni::NOT_STATIC, PlayerEntity, Entity> attackEntity{ *this };
		jni::method<jboolean, "method_2910", jni::NOT_STATIC, BlockPos, Direction> attackBlock{ *this };
	END_KLASS_DEF()


	BEGIN_KLASS_DEF(BlockHitResult, "net/minecraft/class_3965")
		jni::method<Direction, "method_17780", jni::NOT_STATIC> getSide{ *this };
		jni::method<BlockPos, "method_17777", jni::NOT_STATIC> getBlockPos{ *this };
	END_KLASS_DEF()

	BEGIN_KLASS_DEF(MinecraftClient, "net/minecraft/class_310")
		jni::field<MinecraftClient, "field_1700", jni::STATIC> instance{ *this };

		jni::field<ClientWorld, "field_1687"> world{ *this };
		jni::field<ClientPlayerEntity, "field_1724"> player{ *this };
		jni::field<HitResult, "field_1765"> crosshairTarget{ *this };

		jni::field<ClientPlayerInteractionManager, "field_1761"> interactionManager{ *this };

		jni::field<Mouse, "field_1729"> mouse{ *this };
		jni::field<GameOptions, "field_1690"> options{ *this };
		jni::field<RenderTickCounter, "field_1728"> renderTickCounter{ *this };

		jni::method<ClientPlayNetworkHandler, "method_1562"> getNetworkHandler{ *this };
	END_KLASS_DEF()
}