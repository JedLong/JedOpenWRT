include $(TOPDIR)/rules.mk

PKG_NAME:=pupa_cgi
PKG_VERSION:=1.0
PKG_BUILD_DIR:= $(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/pupa_cgi
SECTION:=net
CATEGORY:=Network
TITLE:=pupa cgi
endef

define Package/pupa_cgi/description
	If you can't figure out what this program does, you're probably
	brain-dead and need immediate medical attention.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Package/pupa_cgi/install
	$(INSTALL_DIR) $(1)/pupa-www/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/pupa_cgi $(1)/bin/
endef

$(eval $(call BuildPackage,pupa_cgi))
